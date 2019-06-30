#include "mainwin.h"
#include "donut.h"
#include "to_string.h"

void Mainwin::on_create_order_click() 
{
    if (_store.number_of_customers() == 0) 
    {
       int result = Gtk::MessageDialog{*this, "Create a Customer first!"}.run();
       return;
    }

    Order order;

    Gtk::Dialog *dialog = new Gtk::Dialog{"Create an Order", *this};

    Gtk::Label l_current;
    dialog->get_vbox()->pack_start(l_current, Gtk::PACK_SHRINK);

    Gtk::HBox b_pre;

    Gtk::Label l_pre{"Product:"};
    l_pre.set_width_chars(15);
    b_pre.pack_start(l_pre, Gtk::PACK_SHRINK);

    Gtk::ComboBoxText c_pre;
    for(int i=0; i<_store.number_of_products(); ++i) 
    {
        std::string temp = _store.product_to_string(i);
        c_pre.append(temp);
    }
    b_pre.pack_start(c_pre, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_pre, Gtk::PACK_SHRINK);

    dialog->add_button("Cancel", 0);
    dialog->add_button("Add", 1);
    dialog->add_button("Next", 2);
    dialog->show_all();

    int result; 

    while (true) 
    {
        l_current.set_text(to_string(order));

        result = dialog->run();
        if (result == 0) 
        {
            delete dialog; return;
        }
        if (result == 1) 
        {
            order.add_product(_store.get_product(c_pre.get_active_row_number()));
        }
        if (result == 2) break;
    }

    delete dialog;
    dialog = new Gtk::Dialog{"Select Customer", *this};

    Gtk::ComboBoxText c_cust;
    for (int i=0; i<_store.number_of_customers(); ++i) 
    {
        c_cust.append(_store.customer_to_string(i));
    }
    dialog->get_vbox()->pack_start(c_cust, Gtk::PACK_SHRINK);

    dialog->add_button("Cancel", 0);
    dialog->add_button("Place Order " + std::to_string(order.order_number()), 1);
    dialog->show_all();

    result = dialog->run();

    if (result == 1) 
    {
        _store.place_order(order, c_cust.get_active_row_number());
        set_message("Order " + std::to_string(order.order_number()) + " placed");
    } 
    else
    {
        set_message("Order " + std::to_string(order.order_number()) + " cancelled");
    }
    delete dialog;
}
