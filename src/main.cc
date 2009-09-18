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
#include <iostream>

int main (int argc, char** argv)
{
	std::cout << "1...\n";
	
	Glib::init ();
	
	std::cout << "2...\n";
	
	Glib::thread_init ();
	
	std::cout << "3...\n";
	
	Connection first;

	std::cout << "4...\n";
	
	Glib::RefPtr<Request> richiesta = Request::create ("GET", "hello!");
	
	std::cout << "5...\n";
	
	std::cout << richiesta->url() << "\n";
	return 0;
}
