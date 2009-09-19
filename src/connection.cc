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

#include "connection.h"
#include "config.h"

Request::Request () :
	Glib::ObjectBase (PACKAGE"_Request"),
	_http_method (*this, "http_method"),
	_url (*this, "url"),
	_request_content_type (*this, "request_content_type"),
	_request_headers (*this, "request_headers"),
	_request_body (*this, "request_body"),
	_response_status_code (*this, "response_status_code"),
	_response_reason_phrase (*this, "response_reason_phrase"),
	_response_headers (*this, "response_headers"),
	_response_body (*this, "response_body")
{
	// Useless
}

Glib::RefPtr<Request> Request::create (Glib::ustring http_method, Glib::ustring url)
{
	Request* new_request;
	new_request = new Request ();
	
	new_request->http_method () = http_method;
	new_request->url () = url;
	
	Glib::RefPtr<Request> new_request_ptr (new_request);
	return new_request_ptr;
}

Glib::RefPtr<Request> Request::create (Glib::ustring http_method, Glib::ustring url, Glib::ustring content_type, Glib::ustring request_body)
{
	Request* new_request;
	new_request = new Request ();
	
	new_request->http_method () = http_method;
	new_request->url () = url;
	new_request->request_content_type () = content_type;
	new_request->request_body () = request_body;
	
	Glib::RefPtr<Request> new_request_ptr (new_request);
	return new_request_ptr;
}

Glib::PropertyProxy<Glib::ustring> Request::http_method ()
{
	return Glib::PropertyProxy<Glib::ustring> (this, "http_method");
}

Glib::PropertyProxy<Glib::ustring> Request::url ()
{
	return Glib::PropertyProxy<Glib::ustring> (this, "url");
}

Glib::PropertyProxy<Glib::ustring> Request::request_content_type ()
{
	return Glib::PropertyProxy<Glib::ustring> (this, "content_type");
}

Glib::PropertyProxy<Glib::ustring> Request::request_headers ()
{
	return Glib::PropertyProxy<Glib::ustring> (this, "request_headers");
}

Glib::PropertyProxy<Glib::ustring> Request::request_body ()
{
	return Glib::PropertyProxy<Glib::ustring> (this, "request_body");
}

Glib::PropertyProxy<Glib::ustring> Request::response_status_code ()
{
	return Glib::PropertyProxy<Glib::ustring> (this, "response_status_code");
}

Glib::PropertyProxy<Glib::ustring> Request::response_reason_phrase ()
{
	return Glib::PropertyProxy<Glib::ustring> (this, "response_reason_phrase");
}

Glib::PropertyProxy<Glib::ustring> Request::response_headers ()
{
	return Glib::PropertyProxy<Glib::ustring> (this, "response_headers");
}

Glib::PropertyProxy<Glib::ustring> Request::response_body ()
{
	return Glib::PropertyProxy<Glib::ustring> (this, "response_body");
}

sigc::signal<void> Request::signal_complete ()
{
	return _signal_complete;
}






Connection::Connection ()
{
	authenticated = false;
	captcha_needed = false;
	
	source = PACKAGE"-"VERSION;
	
	session = soup_session_sync_new ();
}


void Connection::request (Glib::RefPtr<Request> request)
{
	// TODO Check if data is correct

}

void Connection::request_thread (Glib::RefPtr<Request> request)
{
	SoupMessage* message = soup_message_new (request->_http_method.get_value().c_str (), request->_url.get_value().c_str ());
	
	if (authenticated)
		soup_message_headers_append (message->request_headers, "Authorization",
		                             Glib::ustring::compose ("GoogleLogin auth=%1", auth_token).c_str ());
	
	if (! (request->_request_content_type.get_value().empty () || request->_request_body.get_value().empty ()))
		// FIXME Worry about the SoupMemoryuse when optimiziation with parameters is done
		soup_message_set_request (message, request->_request_content_type.get_value().c_str (), SOUP_MEMORY_STATIC, request->_request_body.get_value().c_str (), request->_request_body.get_value().bytes ());
	
	unsigned int status;
	status = soup_session_send_message (session, message);
	
	request->_signal_complete.emit ();
}

