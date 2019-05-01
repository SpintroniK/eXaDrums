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

            Gtk::MessageType message_type = static_cast<Gtk::MessageType>(e.type());
            Gtk::MessageDialog d(e.what(), false, message_type, Gtk::ButtonsType::BUTTONS_OK, true);
            d.set_title("Error");
            d.set_keep_above();
            d.run();
    }

}

#endif