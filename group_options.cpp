/*
	A "group option" is a radio button that has been added to a `group` object by the `group::add_option` method.
	This method offers a quick and easy way to create a radio group, freeing the user from having to write the code
	themselves. The `group` object creates and manages all the checkboxes for you, internally forming a radio group
	with them (using the `radio_group` class) and adding them to the `group`'s layout.
*/

#include <nana/gui.hpp>
#include <nana/gui/widgets/group.hpp>
#include <iostream>
#include <vector>

int main()
{
	using namespace nana;

	form fm;
	group grp(fm);

	grp.caption("Group Example");
	grp.move(rectangle{10, 10, 200, 100});

	std::vector<checkbox*> options;
	options.push_back(&grp.add_option("option one"));
	options.push_back(&grp.add_option("option two"));
	options.push_back(&grp.add_option("option three"));

	for(auto option : options)
	{
		/*
			When a checkbox is clicked, print which index it has in the radio group.
			The event handler must be attached to each checkbox rather than the parent
			(group) or ancestors (form), because events don't propagate upwards to 
			a widget's parent or ancestors.
		*/

		option->events().click([&]
		{
			// group::option returns the index of the currently selected option,
			// which is the radio button that was just clicked when this event
			// handler is called
			std::cout << grp.option() << std::endl;
		});
	}

	fm.show();
	exec();
}
