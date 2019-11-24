// Author: Louis Heery (lah119)

#ifndef IMAP_H
#define IMAP_H
#include "imaputils.hpp"
#include <libetpan/libetpan.h>
#include <string>
#include <functional>
#include <iostream>
#include <cassert>
#include <exception>

namespace IMAP {

class Session;

class Message {

	public:
		// Message Class Object Constructor -> sets session = session, and uid = uid.
		Message(Session* session, uint32_t uid) : session(session), uid(uid) {}

		// Function one of the descriptor fields (subject, from, ...) of a Message Object instance
		// INPUT: Fieldname to be returned.
		// OUTPUT: Value of field with name = fieldname
		std::string getField(std::string fieldname);

		// Function gets the Body of a Message from the Mailbox
		// INPUT: none
		// OUTPUT: Body of the Message of the current Message Object instance
		std::string getBody();

		// Function returns UID of specific Message in the Mailbox
		// INPUT: none
		// OUTPUT: UID of the Message of the current Message Object instance
		uint32_t getUID() const;
		
		// Function Fetches a specific Message in the Mailbox
		// INPUT: none
		// OUTPUT: none, but Message Object is Initialised with the Subject, From, Body attribute values
		void fetchMessage();

		// Function Removes the current Message Object instance
		// INPUT: none
		// OUTPUT: none, but Message Object instance is deleted, Message is also marked as 'deleted' on the MailBox server itself
		void deleteFromMailbox();


	private:

		// Message Attributes which store each field of the Message itself as Strings
		std::string body = "";
		std::string from = "";
		std::string subject = "";

		// Stores UID of each message
		uint32_t const uid;

		// Session Object Pointer created within Message Object instance
		Session* session;

		// Function assigns the 'from' attribute of the Message depending on whether From data stored on Server is a Name or an
		// email address.
		// INPUT: none.
		// OUTPUT: none, but 'from' attribute of Message Object instance is assigned
		void specifyFromAddress(clist* frm_list);

		// Get the body of the message. You may chose to either include the headers or not.
		// INPUT: msg_att (type = mailimap_msg_att)
		// OUTPUT: none, but Email Content is retrieved from the MailBox server to the Message object instance
		void getEmailContent(mailimap_msg_att * msg_att);
};


class Session {

	public:

		Session(std::function<void()> updateUI); // Session Class Object Constructor

		std::function<void()> updateUI;

		// Get all messages in the INBOX mailbox terminated by a nullptr
		// INPUT: none
		// OUTPUT: none, but Each Message Object is Created inside of the 'messages' linked list and initialised
		//               with its attribute values
		Message** getMessages();

		// Function Connect to the specified server (143 is the standard unencrypte imap port)
		// INPUT: Server Address and Port Number
		// OUTPUT: none, but client connected to server
		void connect(std::string const& server, size_t port = 143);

		// Function Logs In to the specified server
		// INPUT: User's UserID and Password
		// OUTPUT: none, but client logged on to server
		void login(std::string const& userid, std::string const& password);

		// Function select a specific mailbox on the Server
		// INPUT: Name of Mailbox to be selected
		// OUTPUT: none, but Mailbox is selected
		void selectMailbox(std::string const& mailbox);

		// Function returns the imap object because imap attribute is private
		// INPUT: none
		// OUTPUT: imap attribute variable
		mailimap* getIMAP() const;
		
		// Function deletes all emails from the Session instance except 1 email
		// INPUT: Message UID to Not Delete
		// OUTPUT: none, but all messages in linked list deleted from Session except the Message to keep
		void deleteMessagesFromSessionExcept(uint32_t messageUIDToKeep);

		// Session Class Destructor
		~Session();

	private:
		Message** messages; // Pointer to the first element of Linked List of Pointers to each Message instance
		uint32_t numberOfMessages; // Stores total number of messages in the input 
		mailimap* imap; // imap Object used to communicate with Mail Server

		// Function returns UID for a specific Message
		uint32_t getUIDValue(mailimap_msg_att *msg_att) const;

		// Function returns total number of Message in the Mailbox
		// INPUT: none
		// OUTPUT: Total Number of Messages in the Mailbox on the Mail Server
		uint32_t getNumberOfMessages() const;
};
}

#endif /* IMAP_H */
