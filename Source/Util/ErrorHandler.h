#ifndef SOURCE_UTIL_ERRORHANDLER_H_
#define SOURCE_UTIL_ERRORHANDLER_H_

#include <libexadrums/Util/ErrorHandling.h>

#include <gtkmm/messagedialog.h>

#include <iostream>

namespace Errors
{

    static void errorDialog(const Util::Exception& e, bool printError = true)
    {
        if(printError)
        {
            std::cerr << e.what() << '\n';
        }

        Gtk::MessageType message_type;
        std::string message;

        switch(e.type())
        {

            case Util::errorType::error_type_success: 
                message = "Success"; 
                message_type = static_cast<Gtk::MessageType>(Util::errorType::error_type_success);
                break;

            case Util::errorType::error_type_warning: 
                message = "Warning"; 
                message_type = static_cast<Gtk::MessageType>(Util::errorType::error_type_warning);
                break;

            case Util::errorType::error_type_question: 
                message = "Question"; 
                message_type = static_cast<Gtk::MessageType>(Util::errorType::error_type_question);
                break;

            case Util::errorType::error_type_error: 
                message = "Error"; 
                message_type = static_cast<Gtk::MessageType>(Util::errorType::error_type_error);
                break;

            default: 
                message = "Information"; 
                message_type = static_cast<Gtk::MessageType>(Util::errorType::error_type_other);
                break;
        }

        Gtk::MessageDialog d(e.what(), false, message_type, Gtk::ButtonsType::BUTTONS_OK, true);
        d.set_title(message);
        d.set_keep_above();
        d.run();
    }

    inline void errorDialog(std::string&& text, const Util::errorType& t)
    {
        errorDialog(Util::Exception(std::move(text), t));
    }

}

#endif