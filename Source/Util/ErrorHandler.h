#ifndef SOURCE_UTIL_ERRORHANDLER_H_
#define SOURCE_UTIL_ERRORHANDLER_H_

#include <libexadrums/Api/ErrorHandling.h>

#include <gtkmm/messagedialog.h>

#include <iostream>

namespace Errors
{

    static void errorDialog(const eXaDrumsApi::Exception& e, bool printError = true)
    {
            if(printError)
            {
                std::cerr << e.what() << '\n';
            }

            Gtk::MessageDialog d(e.what(), false, Gtk::MessageType(e.type()), Gtk::ButtonsType::BUTTONS_OK);
            d.set_title("Error");
            d.run();
    }

}

#endif