#ifndef _Plot3d_h
#define _Plot3d_h
#ifdef __GNUC__
#pragma interface
#endif

#include <Settings.h>
#include <PanelFloatText.h>
#include <View3d.h>

class Plot3dScalingMap
	: public Map
{
public:
	Plot3dScalingMap(const Space &domain_);

	void apply(const float in[], float out[]) const;
	void apply_inverse(const float in[], float out[]) const;

	void get_range(float &x_min_, float &x_max_,
			float &y_min_, float &y_max_,
			float &z_min_, float &z_max_) const;
	void set_range(float x_min_, float x_max_,
			float y_min_, float y_max_,
			float z_min_, float z_max_);

private:
	float x_min, x_max;
	float y_min, y_max;
	float z_min, z_max;
	float x_offset, x_scale;
	float y_offset, y_scale;
	float z_offset, z_scale;
};

class Plot3d;

class Plot3dSettings
	: public Settings
{
public:
	Plot3dSettings(const Panel &parent, Plot3d &plot_3d_,
		const char * const x_name,
		const char * const y_name,
		const char * const z_name);
	~Plot3dSettings(void);

	void apply(void);
	void reset(void);

private:
	Plot3d &plot_3d;

	PanelFloatText x_min;
	PanelFloatText x_max;
	PanelFloatText y_min;
	PanelFloatText y_max;
	PanelFloatText z_min;
	PanelFloatText z_max;
};

class Plot3d
	: public View3d
{
public:
	Plot3d(const Space &space,
		const char * const x_name,
		const char * const y_name,
		const char * const z_name,
		const Frame &parent,
		int x = GUI::default_x, int y = GUI::default_y,
		int width = GUI::default_width);
	~Plot3d(void);

	void get_range(float &x_min_, float &x_max_,
			float &y_min_, float &y_max_,
			float &z_min_, float &z_max_) const;
	void set_range(float x_min_, float x_max_,
			float y_min_, float y_max_,
			float z_min_, float z_max_);

	const Map &scaling_map(void) const;
	Scene &background_scene(void);

	void empty(void);

private:
	Plot3dScalingMap scaling_map_;
	Scene background_scene_;
	Plot3dSettings plot_3d_settings;
	ApplyButton apply_button;
	ResetButton reset_button;
};

inline const Map &
Plot3d::scaling_map(void) const
{
	return scaling_map_;
}

inline Scene &
Plot3d::background_scene(void)
{
	return background_scene_;
}

#endif
