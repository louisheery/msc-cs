// Author: Louis Heery (lah119)

#include "imap.hpp"
using namespace IMAP;


Session::Session(std::function<void()> updateUI): updateUI(updateUI), messages(nullptr), numberOfMessages(0){

	// Initialises value of imap Attribute of Session Class
	imap = mailimap_new(0, nullptr);
}

Message** Session::getMessages() {

	numberOfMessages = getNumberOfMessages(); // Fetch number of messages on server
	messages = new Message*[numberOfMessages + 1]; // Create new Message object Linked List

	// If number of messages = 0 -> return nullptr
	if (numberOfMessages == 0){
		messages[0] = nullptr;
		return messages;
  	}

	clist * fetch_result;
	clistiter * cur;

	// Get all messages in the INBOX mailbox terminated by a nullptr
	auto set = mailimap_set_new_interval(1, 0); // Specifies that messages should be fetched in intervals of 1
	auto fetch_att = mailimap_fetch_att_new_uid(); // Attribute which specifies each email
	auto fetch_type = mailimap_fetch_type_new_fetch_att(fetch_att); // Attribute specifies type of info on  email to be retrieved

	// Checks emails were successfully fetched
	int r = mailimap_fetch(imap, set, fetch_type, &fetch_result);
	check_error(r, "Could not fetch email(s).");

	int emailNumber = 0; // Counter to remember which email is being fetched

	// Loops through all emails on server, until nullptr is encountered
	for (cur = clist_begin(fetch_result); cur != nullptr; cur = clist_next(cur)) {

		// Get list of attributes from a clist element
		auto msg_att = (mailimap_msg_att*)clist_content(cur);

		// Get UID value of message from message attribute list
		auto uid = getUIDValue(msg_att);

		if (uid == 0) { // Skips email if uid = 0
			continue;
		} else {
			messages[emailNumber] = new Message(this, uid); // Creates new Message object instance
			messages[emailNumber]->fetchMessage(); // Fetch contents of current email
			emailNumber++; // Increments email number counter by 1
		}
	}

	// Set final item in Messages linked list to nullptr
	messages[emailNumber] = nullptr;

	// Frees the result of a fetch command and mailimap set
	mailimap_fetch_list_free(fetch_result); 
	mailimap_fetch_type_free(fetch_type);
	mailimap_set_free(set);

	return messages;
}

void Message::fetchMessage() {

	auto set = mailimap_set_new_single(uid); // Creates a set with a single message
	auto fetch_type = mailimap_fetch_type_new_fetch_att_list_empty(); // Creates a mailimap_fetch_type structure
	auto env_att = mailimap_fetch_att_new_envelope(); // Creates a mailimap envelope attribute list
	mailimap_fetch_type_new_fetch_att_list_add(fetch_type, env_att); // Add fetch env_att to mailimap_fetch_type

	auto section = mailimap_section_new(NULL); // Creates a mailimap_section structure
	auto fetch_att = mailimap_fetch_att_new_body_section(section); // Creates a mailimap_fetch_att structure to request a given section of a message
	mailimap_fetch_type_new_fetch_att_list_add(fetch_type, fetch_att); // Adds a given fetch attribute to the mailimap_fetch structure
	
	clist * fetch_result;

	// Retrieve data associated with the given message number, and checks if successful
	int r = mailimap_uid_fetch(session->getIMAP(), set, fetch_type, &fetch_result);
	check_error(r, "could not fetch email");

	clistiter *cur = clist_begin(fetch_result);			  // Get firstelement of clist
	auto msg_att = (mailimap_msg_att*)clist_content(cur); // Get the list of attributes from a clist element
	getEmailContent(msg_att); 							  // Get contents of message

	// Frees the result of a fetch command
	mailimap_fetch_list_free(fetch_result);
	mailimap_fetch_type_free(fetch_type);
    mailimap_set_free(set);

	
}

void Message::getEmailContent(mailimap_msg_att * msg_att)
{
	clistiter * cur;

  	// iterate on each result of one given message
	for(cur = clist_begin(msg_att->att_list) ; cur != NULL ; cur = clist_next(cur)) {

		auto item = (mailimap_msg_att_item *)clist_content(cur); // cast content of clist element to a message attribute item

		// Checks item attribute type is not static
		if (item->att_type != MAILIMAP_MSG_ATT_ITEM_STATIC) {
			continue;
		}
	
		// Fetches Fields text (Subject and From)
		if (item->att_data.att_static->att_type == MAILIMAP_MSG_ATT_ENVELOPE) {
			// Fetches Subject text
			if (item->att_data.att_static->att_data.att_env->env_subject) {
				subject = item->att_data.att_static->att_data.att_env->env_subject;
			}

			// Fetches From text
			if (item->att_data.att_static->att_data.att_env->env_from->frm_list) {
				specifyFromAddress(item->att_data.att_static->att_data.att_env->env_from->frm_list);
			}
		}

		// Fetches Body text
		if (item->att_data.att_static->att_type == MAILIMAP_MSG_ATT_BODY_SECTION) {
			if (item->att_data.att_static->att_data.att_body_section->sec_body_part) {
				body = item->att_data.att_static->att_data.att_body_section->sec_body_part;
			}
		}
	}
}

void Message::specifyFromAddress(clist* frm_list) {

	clistiter* cur;

    for (cur = clist_begin(frm_list); cur != nullptr; cur = clist_next(cur)) {
		auto address = (mailimap_address*)clist_content(cur);

		// If From Address is written as the Name of Sender
		if (address->ad_personal_name) {
			from = from + address->ad_personal_name;
		}

		// If From Address is written as an Email Address of Sender
		if (address->ad_mailbox_name && address->ad_host_name) {
			from = from + address->ad_mailbox_name + "@" + address->ad_host_name;
		}
    }
}

std::string Message::getField(std::string fieldname) {

	 // Returns the from or Subject field value
	 if (fieldname == "From") {
		 return from;
	 } else if (fieldname == "Subject") {
		 return subject;
	 } else { // Else return blank Field text
		 return "";
	 }
}

uint32_t Message::getUID() const {
	return uid;
}

std::string Message::getBody() {
	return body;
}

void Message::deleteFromMailbox() {

	auto set = mailimap_set_new_single(uid); // creates a set with a single message
    auto flag_list = mailimap_flag_list_new_empty(); // creates an empty list of flags
    auto deleted = mailimap_flag_new_deleted(); // creates an object representing a deleted flag

    mailimap_flag_list_add(flag_list, deleted); // adds a flag to the list of flags
    auto store = mailimap_store_att_flags_new_set_flags(flag_list); // creates a store attribute to set the given flags

	// Checks message was successfully marked as deleted
	int r = mailimap_uid_store(session->getIMAP(), set, store);
    check_error(r,"Couldn't set the delete flag for this message.");

	// Checks message was successfully deleted
	int r2 = mailimap_expunge(session->getIMAP());
    check_error(r2, "Couldn't delete this message.");

	// Frees the result of the store request
	mailimap_store_att_flags_free(store);
    mailimap_set_free(set);

    // Deletes other messages deleted from session -> Update UI elements -> delete message instance
	session->deleteMessagesFromSessionExcept(uid);
	session->updateUI();
    delete this;

}

void Session::deleteMessagesFromSessionExcept(uint32_t messageUIDToKeep) {
	// Loop through all messages in Inbox
    for (int i = 0; i < numberOfMessages; i++) {

		// Only delete is message UID not equal to the message UID to be kept
		if (messages[i]->getUID() != messageUIDToKeep)
			delete messages[i];
		}
	
	// Then delete messages linked list
    delete [] messages;
}

uint32_t Session::getUIDValue(mailimap_msg_att *msg_att) const {
	clistiter * cur;

	// Loops through each result of the Message with msg_att
	for(cur = clist_begin(msg_att->att_list) ; cur != NULL ; cur = clist_next(cur)) {

		// cast the content of a clist element to a message attribute item
		auto item = (struct mailimap_msg_att_item*)clist_content(cur);

		// Skips if att_type = static
		if (item->att_type != MAILIMAP_MSG_ATT_ITEM_STATIC) {
			continue;
		}

		// Skips if att_data is not equal to attribute uid
		if (item->att_data.att_static->att_type != MAILIMAP_MSG_ATT_UID) {
			continue;
		}

		return item->att_data.att_static->att_data.att_uid;
	}

	return 0;
}

uint32_t Session::getNumberOfMessages() const {

	auto status_att_list = mailimap_status_att_list_new_empty(); // Creates an empty list of status attributes
	mailimap_status_att_list_add(status_att_list, MAILIMAP_STATUS_ATT_MESSAGES); // Adds status attributes to the list

	mailimap_mailbox_data_status * result;

	char mailbox[] = "INBOX"; // Char array stores name of Mailbox

	// Checks number of messages was successfully fetched
	int r = mailimap_status(imap, mailbox, status_att_list, &result);
	check_error(r, "Could not retrieve no. of messages.\n\nError code:");

	// Get a mailimap_status_info value from the first clist
	auto status_info = (mailimap_status_info*)clist_content(clist_begin(result->st_info_list));
    auto value = status_info->st_value;

	// Free status data structure and status attribute list
	mailimap_mailbox_data_status_free(result);
	mailimap_status_att_list_free(status_att_list);

	return value;
}

void Session::connect(std::string const& server , size_t port) {

	// Checks if Server was successfully connected to
	int r = mailimap_socket_connect(imap, server.c_str(), port);
	check_error(r, "Couldn't connect to the server");
}

void Session::login(std::string const& userid, std::string const& password) {

   // Stores the return value to denote if mailimap_login function completed successfully
   // and Checks if Mailbox has been successfully logged in to
   int r = mailimap_login(imap, userid.c_str(), password.c_str());
   check_error(r, "Couldn't login to server");

   if (r == 0) { // IF Mailbox has been successfully selected, r = 0
	   std::cout << "Successfully Logged in";
   }
}

void Session::selectMailbox(std::string const& mailbox) {

   // Stores the return value to denote if mailimap_select function completed successfully
   int r = mailimap_select(imap, "INBOX");
	// Checks if Mailbox has been successfully selected
   check_error(r, "could not select INBOX mailbox");

}

mailimap* Session::getIMAP() const {
	return imap;
}

Session::~Session()
{
    // Deletes all Message Objects from Session Class instance within the linked list
	for (int i = 0; i < numberOfMessages; i++) {
		delete messages[i]; // Deletes each item of the Linked List
    }

    delete [] messages; // Deletes messages Linked List

    mailimap_logout(imap); // Logs out of Mailbox
    mailimap_free(imap); // Frees Allocated Memory
}
