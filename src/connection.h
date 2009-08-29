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

#define GOOGLE_ACCOUNTTYPE_GOOGLE        0x1 // 01
#define GOOGLE_ACCOUNTTYPE_HOSTED        0x2 // 10

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


class Response
{
public:
	unsigned int get_status_code ();
	Glib::ustring get_reason_phrase ();
	Glib::ustring get_message ();
};


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
	
	Response do_request (Glib::ustring http_method, Glib::ustring url, Glib::ustring message);

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

	void request_callback ();
};

