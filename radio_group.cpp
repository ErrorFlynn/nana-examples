#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/checkbox.hpp>
#include <vector>
#include <iostream>

int main()
{
	nana::form fm;

	// use a vector to store the radio buttons
	std::vector<std::unique_ptr<nana::checkbox>> radio_buttons;

	// construct the buttons on the heap and let smart pointers manage the memory
	radio_buttons.emplace_back(new nana::checkbox(fm, "banana"));
	radio_buttons.emplace_back(new nana::checkbox(fm, "apple"));
	radio_buttons.emplace_back(new nana::checkbox(fm, "cherry"));
	radio_buttons.emplace_back(new nana::checkbox(fm, "plum"));

	nana::radio_group rg;
	fm.div("vert margin=15 radio_buttons");

	// set up each radio button
	for(auto &radio_button : radio_buttons)
	{
		// add a click handler to the button
		radio_button->events().click([&](const nana::arg_click &arg)
		{
			std::cout << "button " << rg.checked() << " clicked - " << radio_button->caption() << std::endl;
		});

		// add the button to the form's automatic layout management
		fm["radio_buttons"] << *radio_button;

		// add the button to the radio group
		rg.add(*radio_button);
	}

	// make the third radio button checked by default
	radio_buttons[2]->check(true);
	
	fm.collocate();
	fm.show();
	nana::exec();
}
