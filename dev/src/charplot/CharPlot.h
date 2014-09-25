#ifndef _CharPlot_h
#define _CharPlot_h

#include <fstream>
#include <PanelWin.h>
#include <EventLoop.h>
#include <PanelText.h>
#include <PanelMessage.h>
#include <View2d.h>

class CharPlot
	: public View2d
{
public:
	CharPlot(const Frame &parent, std::ifstream &input);
};

class CharPlotPanelWin;

class FilenameText
	: public PanelText
{
public:
	FilenameText(const Panel &panel, CharPlotPanelWin &char_plot_panel_win_);

private:
	void proc(const char *val);

	PanelMessage message;
	CharPlotPanelWin &char_plot_panel_win;
};

class CharPlotPanelWin
	: public PanelWin
{
public:
	CharPlotPanelWin(const Frame &parent);
	~CharPlotPanelWin(void);

	void show_plot(std::ifstream &input);

private:
	EventLoop event_loop;
	QuitButton quit_button;
	FilenameText filename_text;

	CharPlot *char_plot;
};

#endif
