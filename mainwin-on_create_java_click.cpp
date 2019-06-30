#include "mainwin.h"
#include "java.h"


void Mainwin::on_create_coffee_click() 
{ 
    std::string name;
    double price, cost;

    Gtk::Dialog *dialog = new Gtk::Dialog{"Create Java", *this};

    Gtk::HBox b_name;

    Gtk::Label l_name{"Name:"};
    l_name.set_width_chars(10);
    b_name.pack_start(l_name, Gtk::PACK_SHRINK);

    Gtk::Entry e_name;
    e_name.set_max_length(50);
    b_name.pack_start(e_name, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_name, Gtk::PACK_SHRINK);

    Gtk::HBox b_price;

    Gtk::Label l_price{"Price:"};
    l_price.set_width_chars(10);
    b_price.pack_start(l_price, Gtk::PACK_SHRINK);

    Gtk::Entry e_price;
    e_price.set_max_length(50);
    b_price.pack_start(e_price, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_price, Gtk::PACK_SHRINK);

    Gtk::HBox b_cost;

    Gtk::Label l_cost{"Cost:"};
    l_cost.set_width_chars(10);
    b_cost.pack_start(l_cost, Gtk::PACK_SHRINK);

    Gtk::Entry e_cost;
    e_cost.set_max_length(50);
    b_cost.pack_start(e_cost, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_cost, Gtk::PACK_SHRINK);

    Gtk::HBox b_darkness;

    Gtk::Label l_darkness{"Darkness:"};
    l_darkness.set_width_chars(10);
    b_darkness.pack_start(l_darkness, Gtk::PACK_SHRINK);

    Gtk::ComboBoxText c_darkness;
    c_darkness.set_size_request(160);
    for (auto s: darkness_to_string) c_darkness.append(s);
    b_darkness.pack_start(c_darkness, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_darkness, Gtk::PACK_SHRINK);

    dialog->add_button("Cancel", 0);
    dialog->add_button("Next", 1);
    dialog->show_all();

    int result;
    bool fail = true;  

    while (fail) 
    {
        fail = false;  
        result = dialog->run();
        if (result != 1) 
        {
            delete dialog; return;
        }

        try 
        {
            price = std::stod(e_price.get_text());
        } 
        
        catch(std::exception e) 
        {
            e_price.set_text("Invalid");
            fail = true;
        }
        try 
        {
            cost = std::stod(e_cost.get_text());
        } 
        
        catch(std::exception e) 
        {
            e_cost.set_text("Invalid");
            fail = true;
        }
        
        name = e_name.get_text();
        if (name.size() == 0)
        {
            e_name.set_text("Invalid");
            fail = true;
        }
    }

    Darkness darkness = static_cast<Darkness>(c_darkness.get_active_row_number());
    if (darkness < 0 || darkness >= darkness_to_string.size()) darkness = Blonde;
    Java* java = new Java{name, price, cost, darkness};

    delete dialog;

    dialog = new Gtk::Dialog("Add Shots", *this);

    Gtk::ComboBoxText c_shots;
    c_shots.set_size_request(160);
    for (auto s: shot_to_string) c_shots.append(s);
    dialog->get_vbox()->pack_start(c_shots, Gtk::PACK_SHRINK);

    Gtk::Label l_shots;
    dialog->get_vbox()->pack_start(l_shots, Gtk::PACK_SHRINK);

    dialog->add_button("Cancel", 0);
    dialog->add_button("Create", 1);
    dialog->add_button("Add", 2);
    dialog->show_all();

    while(true) 
    {
        l_shots.set_text(java->to_string());
        result = dialog->run();
        if (result == 0) 
        {
            delete dialog; 
            return;
        }
        if (result == 1) 
        break;
        java->add_shot((Shot)(c_shots.get_active_row_number()));
    }

    _store.add_product(java);
    msg->set_text("New java product \"" + name + "\" created");
    delete dialog;   
}


