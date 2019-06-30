#include "mainwin.h"
#include "java.h"
#include "donut.h"
#include "customer.h"
#include <ostream>
#include <iostream>
#include <regex>
#include <fstream>
#include <iomanip>
#include <sstream>

Mainwin::Mainwin() : _store{Store{"JADE"}} 
{

    set_title("Java and Donut Express (JADE)");
    set_icon_from_file("window_logo.png");
    set_default_size(800, 600);

    Gtk::Box *vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
    add(*vbox);

    Gtk::MenuBar *menubar = Gtk::manage(new Gtk::MenuBar());
    vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);

    Gtk::MenuItem *menuitem_file = Gtk::manage(new Gtk::MenuItem("_File", true));
    menubar->append(*menuitem_file);
    Gtk::Menu *filemenu = Gtk::manage(new Gtk::Menu());
    menuitem_file->set_submenu(*filemenu);

    Gtk::MenuItem *menuitem_save = Gtk::manage(new Gtk::MenuItem("_Save", true));
    menuitem_save->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_save_click));
    filemenu->append(*menuitem_save);

    Gtk::MenuItem *menuitem_load = Gtk::manage(new Gtk::MenuItem("_Load", true));
    menuitem_load->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_load_click));
    filemenu->append(*menuitem_load);

    Gtk::MenuItem *menuitem_quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
    menuitem_quit->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_quit_click));
    filemenu->append(*menuitem_quit);

    Gtk::MenuItem *menuitem_view = Gtk::manage(new Gtk::MenuItem("_View", true));
    menubar->append(*menuitem_view);
    Gtk::Menu *viewmenu = Gtk::manage(new Gtk::Menu());
    menuitem_view->set_submenu(*viewmenu);

    Gtk::MenuItem *menuitem_all_orders = Gtk::manage(new Gtk::MenuItem("All _Orders", true));
    menuitem_all_orders->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_view_orders_click));
    viewmenu->append(*menuitem_all_orders);

    Gtk::MenuItem *menuitem_all_products = Gtk::manage(new Gtk::MenuItem("_All Products", true));
    menuitem_all_products->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_view_all_click));
    viewmenu->append(*menuitem_all_products);

    Gtk::MenuItem *menuitem_list_customers = Gtk::manage(new Gtk::MenuItem("_Customers", true));
    menuitem_list_customers->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_list_customers_click));
    viewmenu->append(*menuitem_list_customers);
  
    Gtk::MenuItem *menuitem_create = Gtk::manage(new Gtk::MenuItem("_Create", true));
    menubar->append(*menuitem_create);
    Gtk::Menu *createmenu = Gtk::manage(new Gtk::Menu());
    menuitem_create->set_submenu(*createmenu);

    menuitem_new_order = Gtk::manage(new Gtk::MenuItem("_Order", true));
    menuitem_new_order->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_create_order_click));
    createmenu->append(*menuitem_new_order);

    menuitem_new_coffee = Gtk::manage(new Gtk::MenuItem("_Coffee", true));
    menuitem_new_coffee->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_create_coffee_click));
    createmenu->append(*menuitem_new_coffee);

    menuitem_new_donut = Gtk::manage(new Gtk::MenuItem("_Donut", true));
    menuitem_new_donut->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_create_donut_click));
    createmenu->append(*menuitem_new_donut);

    Gtk::MenuItem *menuitem_new_customer = Gtk::manage(new Gtk::MenuItem("_Customer", true));
    menuitem_new_customer->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_new_customer_click));
    createmenu->append(*menuitem_new_customer);

    Gtk::MenuItem *menuitem_process = Gtk::manage(new Gtk::MenuItem("_Process", true));
    menubar->append(*menuitem_process);
    Gtk::Menu *processmenu = Gtk::manage(new Gtk::Menu());
    menuitem_process->set_submenu(*processmenu);

    Gtk::MenuItem *menuitem_fill = Gtk::manage(new Gtk::MenuItem("_Fill Order", true));
    menuitem_fill->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_fill_click));
    processmenu->append(*menuitem_fill);

    Gtk::MenuItem *menuitem_pay = Gtk::manage(new Gtk::MenuItem("_Pay for Order", true));
    menuitem_pay->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_pay_click));
    processmenu->append(*menuitem_pay);

    Gtk::MenuItem *menuitem_discard = Gtk::manage(new Gtk::MenuItem("_Discard Order", true));
    menuitem_discard->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_discard_click));
    processmenu->append(*menuitem_discard);

    Gtk::MenuItem *menuitem_help = Gtk::manage(new Gtk::MenuItem("_Help", true));
    menubar->append(*menuitem_help);
    Gtk::Menu *helpmenu = Gtk::manage(new Gtk::Menu());
    menuitem_help->set_submenu(*helpmenu);

    Gtk::MenuItem *menuitem_about = Gtk::manage(new Gtk::MenuItem("About", true));
    menuitem_about->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_about_click));
    helpmenu->append(*menuitem_about);

    Gtk::Toolbar *toolbar = Gtk::manage(new Gtk::Toolbar);
    vbox->add(*toolbar);

    Gtk::Image* view_orders_image = Gtk::manage(new Gtk::Image{"list_orders.png"});
    Gtk::ToolButton *view_orders_button = Gtk::manage(new Gtk::ToolButton{*view_orders_image});
    view_orders_button->set_tooltip_markup("View all orders");
    view_orders_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_view_orders_click));
    toolbar->append(*view_orders_button);

    Gtk::Image* create_order_image = Gtk::manage(new Gtk::Image{"create_order.png"});
    Gtk::ToolButton *create_order_button = Gtk::manage(new Gtk::ToolButton{*create_order_image});
    create_order_button->set_tooltip_markup("Create a new order");
    create_order_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_create_order_click));
    toolbar->append(*create_order_button);

    Gtk::SeparatorToolItem *sep0 = Gtk::manage(new Gtk::SeparatorToolItem());
    toolbar->append(*sep0);

    Gtk::Image* fill_order_image = Gtk::manage(new Gtk::Image{"fill_order.png"});
    Gtk::ToolButton *fill_order_button = Gtk::manage(new Gtk::ToolButton{*fill_order_image});
    fill_order_button->set_tooltip_markup("Fill an order");
    fill_order_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_fill_click));
    toolbar->append(*fill_order_button);

    Gtk::Image* pay_order_image = Gtk::manage(new Gtk::Image{"pay_for_order.png"});
    Gtk::ToolButton *pay_order_button = Gtk::manage(new Gtk::ToolButton{*pay_order_image});
    pay_order_button->set_tooltip_markup("Pay for an order");
    pay_order_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_pay_click));
    toolbar->append(*pay_order_button);

    Gtk::Image* discard_order_image = Gtk::manage(new Gtk::Image{"discard_order.png"});
    Gtk::ToolButton *discard_order_button = Gtk::manage(new Gtk::ToolButton{*discard_order_image});
    discard_order_button->set_tooltip_markup("discard a new order");
    discard_order_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_discard_click));
    toolbar->append(*discard_order_button);

    Gtk::SeparatorToolItem *sep1 = Gtk::manage(new Gtk::SeparatorToolItem());
    toolbar->append(*sep1);

    Gtk::Image* view_all_image = Gtk::manage(new Gtk::Image{"list_products.png"});
    Gtk::ToolButton *view_all_button = Gtk::manage(new Gtk::ToolButton{*view_all_image});
    view_all_button->set_tooltip_markup("View all products");
    view_all_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_view_all_click));
    toolbar->append(*view_all_button);

    Gtk::Image* new_java_image = Gtk::manage(new Gtk::Image{"new_java.png"});
    Gtk::ToolButton *new_java_button = Gtk::manage(new Gtk::ToolButton{*new_java_image});
    new_java_button->set_tooltip_markup("View all products");
    new_java_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_create_coffee_click));
    toolbar->append(*new_java_button);

    Gtk::Image* new_donut_image = Gtk::manage(new Gtk::Image{"new_donut.png"});
    Gtk::ToolButton *new_donut_button = Gtk::manage(new Gtk::ToolButton{*new_donut_image});
    new_donut_button->set_tooltip_markup("View all products");
    new_donut_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_create_donut_click));
    toolbar->append(*new_donut_button);

    Gtk::SeparatorToolItem *sep2 = Gtk::manage(new Gtk::SeparatorToolItem());
    toolbar->append(*sep2);

    Gtk::Image *list_customers_image = Gtk::manage(new Gtk::Image{"list_customers.png"});
    Gtk::ToolButton *list_customers_button = Gtk::manage(new Gtk::ToolButton(*list_customers_image));
    list_customers_button->set_tooltip_markup("List all customers");
    list_customers_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_list_customers_click));
    toolbar->append(*list_customers_button);

    Gtk::Image *new_customer_image = Gtk::manage(new Gtk::Image{"new_customer.png"});
    Gtk::ToolButton *new_customer_button = Gtk::manage(new Gtk::ToolButton(*new_customer_image));
    new_customer_button->set_tooltip_markup("Create a new customer");
    new_customer_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_new_customer_click));
    toolbar->append(*new_customer_button);

    Gtk::Label* main_area = Gtk::manage(new Gtk::Label);
    main_area->set_hexpand(true);    
    main_area->set_vexpand(true);
    vbox->add(*main_area);

    Gtk::Box *hbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 0));

    msg = Gtk::manage(new Gtk::Label());
    msg->set_hexpand(true);
    vbox->add(*msg);

    cash = Gtk::manage(new Gtk::Label());
    hbox->add(*cash);

    vbox->add(*hbox);
    update_cash();

    vbox->show_all();
}

Mainwin::~Mainwin() { }

void Mainwin::on_quit_click() 
{         
    close();
}

void Mainwin::on_view_orders_click() 
{ 
    process_order(Action::Show);
}

void Mainwin::on_view_products_click() 
{
    set_message("");
    std::ostringstream oss;
    oss << _store << std::endl;
    Gtk::MessageDialog d{*this, "List of Products"}; 
    d.set_secondary_text(oss.str());
    int result = d.run();
}

void Mainwin::on_view_all_click() 
{ 
    msg->set_text("");
    std::ostringstream oss;
    oss << _store << std::endl;
    Gtk::MessageDialog d{*this, "List of Products"}; 
    d.set_secondary_text(oss.str());
    int result = d.run();
}

void Mainwin::on_new_customer_click() 
{
    Gtk::Dialog *dialog = new Gtk::Dialog("Create a Customer", *this);
    Gtk::HBox b_name;

    Gtk::Label l_name{"Name:"};
    l_name.set_width_chars(15);
    b_name.pack_start(l_name, Gtk::PACK_SHRINK);

    Gtk::Entry e_name;
    e_name.set_max_length(50);
    b_name.pack_start(e_name, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_name, Gtk::PACK_SHRINK);

    Gtk::HBox b_phone;

    Gtk::Label l_phone{"Phone:"};
    l_phone.set_width_chars(15);
    b_phone.pack_start(l_phone, Gtk::PACK_SHRINK);

    Gtk::Entry e_phone;
    e_phone.set_max_length(50);
    b_phone.pack_start(e_phone, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_phone, Gtk::PACK_SHRINK);

    dialog->add_button("Cancel", 0);
    dialog->add_button("Create", 1);
    dialog->show_all();

    int result;
    std::string name, phone;
    std::regex re_phone{"[(]?(\\d{3,3}[-)])?\\d{3,3}-\\d{4,4}"};
    bool fail = true;  

    while (fail) 
    {
        fail = false;  
        result = dialog->run();
        if (result != 1) 
        {
            delete dialog; 
            return;
        }
        name = e_name.get_text();
        if (name.size() == 0) 
        {
            e_name.set_text("### Invalid ###");
            fail = true;
        }
        phone = e_phone.get_text();
        if(!std::regex_match(phone,re_phone)) 
        {
            e_phone.set_text("### Invalid ###");
            fail = true;
        }        
    }

    Customer* customer = new Customer{name, phone};
    _store.add_customer(customer);
    set_message("Created customer " + name);

    delete dialog;
}

void Mainwin::on_list_customers_click() 
{
    msg->set_text("");
    std::ostringstream oss;
    for (int i=0; i<_store.number_of_customers(); ++i) 
    {
        oss << _store.customer_to_string(i) << std::endl;
    }
    Gtk::MessageDialog d{*this, "List of Customers"};
    d.set_secondary_text(oss.str());
    int result = d.run();
}

void Mainwin::on_fill_click() 
{
    process_order(Action::Fill);
} 

void Mainwin::on_pay_click() 
{
    process_order(Action::Pay);
} 

void Mainwin::on_discard_click() 
{
    process_order(Action::Discard);
} 

void Mainwin::on_about_click() 
{
    Gtk::MessageDialog *dialog = new Gtk::MessageDialog{"Java and Donut Express"};
    dialog->run();
}

void Mainwin::set_message(std::string message) 
{ 
    msg->set_text(message);
}

void Mainwin::update_cash() 
{ 
    std::ostringstream oss;
    oss << '$' << std::setprecision(2) << std::fixed << _store.cash();
    cash->set_text(oss.str());
}

void Mainwin::on_save_click()
{
    Gtk::Dialog *dialog = Gtk::manage(new Gtk::Dialog);
    dialog->set_title("Filename");
    Gtk::Label *label = Gtk::manage(new Gtk::Label("Enter Filename :"));
    dialog->get_content_area()->pack_start(*label);
    Gtk::Entry *entry = Gtk::manage(new Gtk::Entry);
    entry->set_max_length(50);
    dialog->get_vbox()->pack_start(*entry);
    dialog->add_button("Cancel",0);
    dialog->add_button("Ok",1);
    dialog->show_all();
    int result = dialog->run();
    if(result == 0)
        return;
    _filename = entry->get_text();
    dialog->close();
    while(Gtk::Main::events_pending()) Gtk::Main::iteration();
    std::ofstream ofs{_filename};
    if(ofs)
        _store.save(ofs);
    else
    {
        Gtk::MessageDialog *dialog = new Gtk::MessageDialog{"Unable to save"};
        dialog->run();
        while(Gtk::Main::events_pending()) Gtk::Main::iteration();
    }
}

void Mainwin::on_load_click()
{
    Gtk::Dialog *dialog = Gtk::manage(new Gtk::Dialog);
    dialog->set_title("Filename");
    Gtk::Label *label = Gtk::manage(new Gtk::Label("Enter Filename :"));
    dialog->get_content_area()->pack_start(*label);
    Gtk::Entry *entry = Gtk::manage(new Gtk::Entry);
    entry->set_max_length(50);
    dialog->get_vbox()->pack_start(*entry);
    dialog->add_button("Cancel",0);
    dialog->add_button("Ok",1);
    dialog->show_all();
    int result = dialog->run();
    if(result == 0)
        return;
    _filename = entry->get_text();
    dialog->close();
    while(Gtk::Main::events_pending()) Gtk::Main::iteration();
    std::ifstream ist{_filename};
    if(ist)
        _store = Store{ist};
    else
    {
        Gtk::MessageDialog *dialog = new Gtk::MessageDialog{"Unable to save"};
        dialog->run();
        while(Gtk::Main::events_pending()) Gtk::Main::iteration();
    } 
}

void Mainwin::process_order(Action action) 
{
    std::map<Action, std::string> action_title;
    std::map<Action, std::string> action_button;
    std::map<Action, std::string> action_message;
    action_title[Action::Show] = "Show Order"; 
    action_title[Action::Fill] = "Select an Order to Fill";
    action_button[Action::Fill] = "Fill";
    action_message[Action::Fill] = "Filled Order ";
    action_title[Action::Pay] = "Select an Order to Pay";
    action_button[Action::Pay] = "Pay";
    action_message[Action::Pay] = "Paid Order ";
    action_title[Action::Discard] = "Select an Order to Discard";
    action_button[Action::Discard] = "Discard";
    action_message[Action::Discard] = "Discarded Order ";

    set_message("");
    Gtk::Dialog *dialog = new Gtk::Dialog{action_title[action], *this};

    Gtk::Label l_current;
    dialog->get_vbox()->pack_start(l_current, Gtk::PACK_SHRINK);

    Gtk::HBox b_orders;

    Gtk::Label l_orders{"Order:"};
    l_orders.set_width_chars(15);
    b_orders.pack_start(l_orders, Gtk::PACK_SHRINK);

    std::vector<int> combo_to_order;
    Gtk::ComboBoxText c_orders;
    for(int i=0; i<_store.number_of_orders(); ++i) 
    {
        if ((action == Action::Show) || (action == Action::Fill && _store.order_is_pending(i) && !_store.order_is_filled(i)) ||
            (action == Action::Pay && _store.order_is_pending(i) && !_store.order_is_paid(i)) || 
            (action == Action::Discard && _store.order_is_pending(i))) 
        {
            c_orders.append(std::to_string(i));
            combo_to_order.push_back(i);
        }
    }
    if (combo_to_order.empty()) 
    {
        l_current.set_text("No Eligible Orders");
    } 
    else 
    {
        b_orders.pack_start(c_orders, Gtk::PACK_SHRINK);
        dialog->get_vbox()->pack_start(b_orders, Gtk::PACK_SHRINK);
    }

    dialog->add_button("Close", 0);
    if (!combo_to_order.empty()) 
    {
        dialog->add_button("Show", 1);
        if (action != Action::Show) dialog->add_button(action_button[action], 2);
    }
    dialog->show_all();

    int result;

    while (true) 
    {
        result = dialog->run();
        if (result == 0) 
        {
            delete dialog; 
            return;
        } 
        else if (result == 1) 
        {
            l_current.set_text(_store.order_to_string(combo_to_order[c_orders.get_active_row_number()]));
        } 
        else if (result == 2) 
        {
            if (action == Action::Fill)    _store.fill_order   (combo_to_order[c_orders.get_active_row_number()]);
            if (action == Action::Pay)     _store.pay_order    (combo_to_order[c_orders.get_active_row_number()]);
            if (action == Action::Discard) _store.discard_order(combo_to_order[c_orders.get_active_row_number()]);
            set_message(action_message[action] + std::to_string(combo_to_order[c_orders.get_active_row_number()]));
            update_cash();
            delete dialog;
            return;
        } 
        else 
        {
            throw std::runtime_error{"Invalid dialog response"};
        }
    }
}


