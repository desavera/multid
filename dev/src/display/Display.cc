#include <Scene.h>
#include <Display.h>

FilenameText::FilenameText(const Panel &panel, Display &display_)
	: PanelText(panel, 50),
	  display(display_)
{
	display_label("Input file");
	value("");
}

void
FilenameText::proc(const char *val)
{
	std::ifstream input(val);
	if (!input) {
		display.message.display_label("File not found.");
		display.frame_slider.min_value(0);
		display.frame_slider.max_value(0);
		display.frame_slider.value(0);
		display.frame_slider.active(0);
		return;
	}

	display.busy(1);
	display.read_frames(input);
	display.busy(0);
	if (!input) {
		display.message.display_label("Error reading file.");
		display.frame_slider.min_value(0);
		display.frame_slider.max_value(0);
		display.frame_slider.value(0);
		display.frame_slider.active(0);
		return;
	}

	display.message.display_label("");
	display.frame_slider.min_value(1);
	display.frame_slider.max_value(display.n_frames());
	display.frame_slider.value(1);
	display.frame_slider.active(1);

	display.show_frame(0);
}

FrameSlider::FrameSlider(const Panel &panel, Display &display_)
	: PanelSlider(panel, 1, 300),
	  display(display_)
{
	display_label("Frame number");
	min_value(0);
	max_value(0);
	value(0);
	active(0);
}

void
FrameSlider::proc(int val)
{
	int frame = val - 1;
	if (frame < 0)
		frame = 0;
	if (frame >= display.n_frames())
		frame = display.n_frames() - 1;

	display.show_frame(frame);
}

Display::Display(const Frame &parent)
	: PanelWin(parent),
	  event_loop(),
	  quit_button(panel(), event_loop),
	  filename_text(panel(), *this),
	  message(panel(), " "),
	  frame_slider(panel(), *this),
	  space(0),
	  scene(0),
	  n_frames_(0),
	  view2d(0),
	  view3d(0)
{
	display_label("display");
}

Display::~Display(void)
{
	delete view3d;
	delete view2d;
	delete scene;
	delete space;
}

void
Display::show_frame(int frame)
{
	if (view2d != 0) {
		view2d->empty();
		view2d->add((*scene)[frame]);
	}
	if (view3d != 0) {
		view3d->empty();
		view3d->add((*scene)[frame]);
	}
}

void
Display::read_frames(std::ifstream &input)
{
	delete view3d;
	view3d = 0;
	delete view2d;
	view2d = 0;
	delete scene;
	scene = 0;
	delete space;
	space = 0;

	const int MAX = 80;
	char buf[MAX];

	input >> buf;	// "#Space"
	if (!input) return;
	space = new Space(input);
	if (!input) return;
	// std::cerr << *space;

	// TODO:  Calculate the bounding box from the input.
	if (space->dim() == 2) {
		Bounds2d bounds2d;
		input >> bounds2d;
		if (!input) return;
		// std::cerr << bounds2d;

		view2d = new View2d(*space, parent());
		view2d->bounds(bounds2d);
		view2d->show();
	}
	else {
		Bounds3d bounds3d;
		input >> bounds3d;
		if (!input) return;
		// std::cerr << bounds3d;

		view3d = new View3d(*space, parent());
		view3d->bounds(bounds3d);
		view3d->show();
	}

	input >> buf;	// "#Scene"
	if (!input) return;
	scene = new Scene(*space, input);
	if (!input) return;
	// std::cerr << *scene;

	n_frames_ = scene->n_geom_objs();
}
