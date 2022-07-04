#include "../srv/net.cpp"
#include "./lib/include/Wt/WApplication.h"
#include "./lib/include/Wt/WBreak.h"
#include "./lib/include/Wt/WContainerWidget.h"
#include "./lib/include/Wt/WLineEdit.h"
#include "./lib/include/Wt/WPushButton.h"
#include "./lib/include/Wt/WText.h"


#include <iostream>
#include <thread>
#include <chrono>

class HelloApplication : public Wt::WApplication
{
	public:
		HelloApplication(const Wt::WEnvironment &env);

	private:
		Wt::WLineEdit *nameEdit_;
		Wt::WText *greeting_;
};




HelloApplication::HelloApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
{
    setTitle("Hello world");

    root()->addWidget(std::make_unique<Wt::WText>("Your name, please? "));
    nameEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
    Wt::WPushButton *button = root()->addWidget(std::make_unique<Wt::WPushButton>("Greet me."));
    root()->addWidget(std::make_unique<Wt::WBreak>());
    greeting_ = root()->addWidget(std::make_unique<Wt::WText>());
    auto greet = [this]{
      greeting_->setText("Hello there, " + nameEdit_->text());
    };
    button->clicked().connect(greet);
}

int main(int argc, char **argv)
{
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
      return std::make_unique<HelloApplication>(env);
    });
}
