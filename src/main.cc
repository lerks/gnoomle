

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
	
	/// This method is used to authenticate
	/** You have to pass the account type, the username, the password and the service you want access for.
	    If the authentication fails, an exception is thrown. You can also check if you're authenticated using the is_authenticated() method.
	    The login parameters you provide here will be stored to automatically login again if, for example, the session expires.
	*/
	void authenticate (unsigned int account_type, Glib::ustring username, Glib::ustring password, Glib::ustring service);
	void authenticate (unsigned int account_type, Glib::ustring username, Glib::ustring password, Glib::ustring service, Glib::ustring source);
	
	/// This method allows you to check if the login was successful or not
	bool is_authenticated ();
	
	/// Use this method to get the URL of the captcha
	/** You have to use this method only if authenticate() returns a CaptchaRequired exception. If no captcha is required, the method will return an empty string.
	    It's up to you to show the captcha image to the user and to ask for a response. The response has to be passed as an argument to set_captcha_response()
	*/
	Glib::ustring get_captcha_url ();
	/// This method is used to login again after a captcha test
	/** Pass the user response to this method and the login will be tried again. 
	    If it fails again an exception is thrown, exactly as you were using the authenticate() method.
	*/
	void set_captcha_response (Glib::ustring response);

private:
	bool is_authenticated;
	bool captcha_needed;
	
	unsigned int account_type;
	Glib::ustring username;
	Glib::ustring password;
	Glib::ustring service;
	Glib::ustring source;
};
