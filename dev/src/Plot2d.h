#ifndef _Plot2d_h
#define _Plot2d_h
#ifdef __GNUC__
#pragma interface
#endif

#include <Settings.h>
#include <PanelFloatText.h>
#include <View2d.h>

class Plot2dScalingMap
	: public Map
{
public:
	Plot2dScalingMap(const Space &domain_, bool square_window_);

	void apply(const float in[], float out[]) const;
	void apply_inverse(const float in[], float out[]) const;

	void get_range(float &x_min_, float &x_max_,
		float &y_min_, float &y_max_) const;
	void set_range(float x_min_, float x_max_,
		float y_min_, float y_max_);

private:
	bool square_window;
	float x_min, x_max;
	float y_min, y_max;
	float x_offset, x_scale;
	float y_offset, y_scale;
};

class Plot2d;

class Plot2dSettings
	: public Settings
{
public:
	Plot2dSettings(const Panel &parent, Plot2d &plot_2d_,
		const char * const x_name, const char * const y_name);
	~Plot2dSettings(void);

	void apply(void);
	void reset(void);

private:
	Plot2d &plot_2d;

	PanelText x_range;
	PanelText y_range;
};

class Plot2d
	: public View2d
{
public:
	Plot2d(const Space &space,
		const char * const x_name,
		const char * const y_name,
		const Frame &parent,
		int x = GUI::default_x, int y = GUI::default_y,
		int width = GUI::default_width, bool square_window = false);
	~Plot2d(void);

	void get_range(float &x_min_, float &x_max_,
		float &y_min_, float &y_max_) const;
	void set_range(float x_min_, float x_max_,
		float y_min_, float y_max_);

	const Map &scaling_map(void) const;
	Scene &background_scene(void);

	void empty(void);

private:
	Plot2dScalingMap scaling_map_;
	Scene background_scene_;
	Plot2dSettings plot_2d_settings;
	ApplyButton apply_button;
	ResetButton reset_button;
};

inline const Map &
Plot2d::scaling_map(void) const
{
	return scaling_map_;
}

inline Scene &
Plot2d::background_scene(void)
{
	return background_scene_;
}

#endif
