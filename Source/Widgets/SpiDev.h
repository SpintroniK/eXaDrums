#ifndef EXADRUMS_SOURCE_WIDGETS_SPIDEV_H
#define EXADRUMS_SOURCE_WIDGETS_SPIDEV_H

#include <libexadrums/Api/Config/SpiDevParameters_api.h>

#include <gtkmm/grid.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/adjustment.h>

#include <string>

namespace Widgets
{
    
    class SpiDev : public Gtk::Grid
    {
    public:
        SpiDev(const eXaDrumsApi::SpiDevParameters& params)
        {
            name.set_text(params.name);
            
            cs.get_adjustment()->set_value(params.cs);
            bus.get_adjustment()->set_value(params.bus);

            this->set_column_spacing(4);
            this->set_row_spacing(4);

            this->set_margin_left(4);
            this->set_margin_right(4);
            this->set_margin_top(4);
            this->set_margin_bottom(4);

            this->attach(name, 0, 0, 1, 1);
            this->attach_next_to(bus, name, Gtk::PositionType::POS_RIGHT, 1, 1);
            this->attach_next_to(cs, bus, Gtk::PositionType::POS_RIGHT, 1, 1);

            this->show_all();
        }

    private:

        Gtk::Entry name{};

        Glib::RefPtr<Gtk::Adjustment> busAdj{Gtk::Adjustment::create(0, 0, 10)};
        Gtk::SpinButton bus{busAdj};

        Glib::RefPtr<Gtk::Adjustment> csAdj{Gtk::Adjustment::create(0, 0, 10)};
        Gtk::SpinButton cs{csAdj};
        
    };


} // namespace Widgets


#endif /* EXADRUMS_SOURCE_WIDGETS_SPIDEV_H */
