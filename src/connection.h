/* Gnoomle - A library for the Google Data API written using Gnome technologies
 * Copyright (C) 2009  Luca Wehrstedt
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#define GOOGLE_ACCOUNTTYPE_GOOGLE        0x2 // 10
#define GOOGLE_ACCOUNTTYPE_HOSTED        0x1 // 01

#define GOOGLE_SERVICE_ANALYTICS         "analytics"
#define GOOGLE_SERVICE_APPS              "apps"
#define GOOGLE_SERVICE_BASE              "gbase"
#define GOOGLE_SERVICE_BLOGGER           "blogger"
#define GOOGLE_SERVICE_BOOKSEARCH        "print"
#define GOOGLE_SERVICE_CALENDAR          "cl"
#define GOOGLE_SERVICE_CODESEARCH        "codesearch"
#define GOOGLE_SERVICE_CONTACTS          "cp"
#define GOOGLE_SERVICE_DOCUMENTS         "writely"
#define GOOGLE_SERVICE_FINANCE           "finance"
#define GOOGLE_SERVICE_MAIL              "mail"
#define GOOGLE_SERVICE_HEALTH            "health"
#define GOOGLE_SERVICE_MAPS              "local"
#define GOOGLE_SERVICE_NOTEBOOK          "notebook"
#define GOOGLE_SERVICE_PICASA            "lh2"
#define GOOGLE_SERVICE_SPREADSHEETS      "wise"
#define GOOGLE_SERVICE_WEBMASTERTOOLS    "sitemaps"
#define GOOGLE_SERVICE_YOUTUBE           "youtube"


#include <glibmm.h>
#include <libxml++/libxml++.h>
#include <libsoup/soup.h>

class Request;



/// A class used to connect to Google, wich provides some helper methods for HTTP requests
/** Using this class you can either authenticate to Google to access private data or not, to get only public data.
    Then you can use its helper methods to make requests to Google and retrieve data. The authorization token will be added automatically.
    You can get and provide the data for the HTTP request in a string representation or in a XML representation.
*/
class Connection
{
public:
	/// The constructor provides a ready-to-use not-authenticated Connection object you can use to access Google
	Connection ();
	
	/// Authentication method
	/** You have to pass the account type, the username, the password and the service you want access for.
	    If the authentication fails, an exception is thrown.
	    You can also check if the login was successful using the is_authenticated() method.
	    The login parameters provided here will be stored to automatically login again if, for example, the session expires.
	*/
	void authenticate (unsigned int account_type, Glib::ustring username, Glib::ustring password, Glib::ustring service);
	/// Alternative authentication method
	/** Use this method to authenticate if you want to provide your own "source" parameter to Google, instead of the library one
	*/
	void authenticate (unsigned int account_type, Glib::ustring username, Glib::ustring password, Glib::ustring service, Glib::ustring source);
	
	/// This method allows you to check if the login was successful or not
	bool is_authenticated ();
	
	/// Use this method to get the URL of the captcha
	/** You have to use this method only if authenticate() returns a CaptchaRequired exception.
	    If no captcha is required, the method will return an empty string.
	    It's up to you to show the captcha image to the user and to ask for a response.
	    The response has to be passed as an argument to set_captcha_response()
	*/
	Glib::ustring get_captcha_url ();
	/// This method is used to login again after a captcha test
	/** Pass the user response to this method and the login will be tried again. 
	    If it fails again an exception is thrown, exactly as you were using the authenticate() method.
	*/
	void set_captcha_response (Glib::ustring response);
	
	/// Make a basic request
	/** This is the most basic method to make a request, either with the GET or the POST method.
	    If you use this method you have to specify many parameters.
	    You can alternatively use other methods which automatically specify some oh these for you.
	    The request is done asynchronously. So you have to specify the callback by passing a sigc::slot.
	    The callback data of this method is a pointer Request object. To have other data types use other methods.
	    The callback has to be declared void.
	*/
	void request (Glib::RefPtr<Request> request);

private:
	SoupSession *session;

	bool authenticated;
	bool captcha_needed;

	unsigned int account_type;
	Glib::ustring username;
	Glib::ustring password;
	Glib::ustring service;
	Glib::ustring source;
	Glib::ustring auth_token;
	
	void request_thread (Glib::RefPtr<Request> request);
};



/// A representation of a request
class Request : public Glib::Object
{
public:
	/// Create an instance of this class
	/** This method return a Glib::RefPtr pointing to an instance of this class.
	    You have to pass the HTTP method and the destination URL.
	    If you use this method you probably want to use the "GET" HTTP method.
	    If you want to use "POST" you have to use the other create() method or you have to specify the content of the request using the appropriate methods.
	*/
	static Glib::RefPtr<Request> create (Glib::ustring http_method, Glib::ustring url);
	/// Create an instance of this class
	/** This method return a Glib::RefPtr pointing to an instance of this class.
	    You have to pass the HTTP method, the destination URL and the content type and body of the request.
	    If you use this method you probably want to use the "POST" HTTP method.
	    If you want to use "GET" you should use the other create() method since it doesn't requeire you to set any information about the request.
	*/
	static Glib::RefPtr<Request> create (Glib::ustring http_method, Glib::ustring url, Glib::ustring content_type, Glib::ustring request_body);
	
	/// Obtain the signal to which you can connect you handler
	/** The sigc::signal returned can be used to connect a handler using the connect() method.
	    The signal will be emitted and all handlers will be called when the request has completed and the response is ready to be read.
	    FIXME To make the request begin you have to call the Connection::request() method passing an instance of this class as an argument.
	    The sigc::connection object returned form the connect() method can be used to disconnect the handler.
	*/
	sigc::signal<void> signal_complete ();
	
	/// Get and set the HTTP method used for the request
	/** It can be either GET or POST
	*/
	Glib::PropertyProxy<Glib::ustring> http_method ();
	/// Get and set the URL of the request
	Glib::PropertyProxy<Glib::ustring> url ();
	
	/// Get and set the content type of the request, if any
	Glib::PropertyProxy<Glib::ustring> request_content_type ();
	/// Get and set the headers of the request, if any
	Glib::PropertyProxy<Glib::ustring> request_headers ();
	/// Get and set the body of the request message, if any
	Glib::PropertyProxy<Glib::ustring> request_body ();
	
	/// Get the status code of the response, if the request has completed
	Glib::PropertyProxy<Glib::ustring> response_status_code ();
	/// Get the reason phrase of the response, if the request has completed
	Glib::PropertyProxy<Glib::ustring> response_reason_phrase ();
	/// Get the headers of the response, if the request has completed
	Glib::PropertyProxy<Glib::ustring> response_headers ();
	/// Get the body of the response message, if the request has completed
	Glib::PropertyProxy<Glib::ustring> response_body ();
	
	friend class Connection;
	
	
private:
	/// The signal that is emitted when the response is ready to be read
	/** Every sigc::slot connected to this signal will be called when the request has completed and the response is ready to be read.
	    Handlers, though, cannot be connected directly to this signal but has to be connected using the signal_finished_connect() method.
	*/
	sigc::signal<void> _signal_complete;
	
	Glib::Property<Glib::ustring> _http_method;
	Glib::Property<Glib::ustring> _url;
	
	Glib::Property<Glib::ustring> _request_content_type;
	Glib::Property<Glib::ustring> _request_headers;
	Glib::Property<Glib::ustring> _request_body;
	
	Glib::Property<Glib::ustring> _response_status_code;
	Glib::Property<Glib::ustring> _response_reason_phrase;
	Glib::Property<Glib::ustring> _response_headers;
	Glib::Property<Glib::ustring> _response_body;
	
	/// The default constructor
	// FIXME: maybe it should decalred protected?
	Request ();
};



