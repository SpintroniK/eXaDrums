#ifndef EXADRUMS_SOURCE_WIDGETS_SPIDEV_H
#define EXADRUMS_SOURCE_WIDGETS_SPIDEV_H

#include <libexadrums/Api/Config/SpiDevParameters_api.h>

#include <gtkmm/grid.h>
#include <gtkmm/entry.h>

#include <string>

namespace Widgets
{
    
    class SpiDev : public Gtk::Grid
    {
    public:
        SpiDev(const eXaDrumsApi::SpiDevParameters& params)
        {
            name.set_text(params.name);
            bus.set_text(std::to_string(params.bus));

            this->attach(name, 0, 0, 1, 1);
            this->attach_next_to(bus, name, Gtk::PositionType::POS_RIGHT, 1, 1);

            this->show_all();
        }

    private:

        Gtk::Entry name{};
        Gtk::Entry bus{};
        
    };


} // namespace Widgets


#endif /* EXADRUMS_SOURCE_WIDGETS_SPIDEV_H */
