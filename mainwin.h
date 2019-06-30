#ifndef __MAINWIN_H__
#define __MAINWIN_H__

#include <gtkmm.h>
#include "store.h"

class Mainwin : public Gtk::Window
{
 
    private:
        Store _store;
        Gtk::Label *msg;  
        void set_message(std::string message);
        Gtk::Label *cash;        
        void update_cash();                    
        Gtk::MenuItem *menuitem_new_coffee;   
        Gtk::MenuItem *menuitem_new_donut;
        Gtk::MenuItem *menuitem_new_order;
        std::string _filename;

        enum class Action {Show, Fill, Pay, Discard};
        void process_order(Action action);
    
    public:
        Mainwin();
        virtual ~Mainwin();     

    protected:
        void on_quit_click();       
        void on_view_all_click(); 
        void on_create_coffee_click(); 
        void on_create_donut_click();    
        void on_list_customers_click(); 
        void on_new_customer_click();   
        void on_about_click(); 
        void on_save_click();
        void on_load_click();
        void on_view_orders_click();
        void on_view_products_click();
        void on_create_order_click();
        void on_fill_click();         
        void on_pay_click();      
        void on_discard_click();        
};
#endif 

