#include "mainwin.h"
#include <gtkmm.h>

int main(int argc, char** argv) 
{
   auto app = Gtk::Application::create(argc, argv, "edu.uta.cse1325.jade");
   Mainwin win;
   return app->run(win);
}
