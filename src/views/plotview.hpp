/*
 * This file is part of the SmuView project.
 *
 * Copyright (C) 2017 Frank Stettner <frank-stettner@gmx.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef VIEWS_PLOTVIEW_HPP
#define VIEWS_PLOTVIEW_HPP

#include <memory>

#include <QAction>
#include <QToolBar>

#include "src/views/baseview.hpp"

using std::shared_ptr;

namespace sv {

class Session;

namespace channels {
class BaseChannel;
}

namespace data {
class AnalogSignal;
class BaseCurve;
}

namespace widgets {
class Plot;
}

namespace views {

class PlotView : public BaseView
{
	Q_OBJECT

public:
	PlotView(const Session& session,
		shared_ptr<channels::BaseChannel> channel,
		QWidget* parent = nullptr);
	PlotView(const Session& session,
		shared_ptr<data::AnalogSignal> signal,
		QWidget* parent = nullptr);
	PlotView(const Session& session,
		shared_ptr<data::AnalogSignal> x_signal,
		shared_ptr<data::AnalogSignal> y_signal,
		QWidget* parent = nullptr);

	QString title() const;

private:
	void setup_ui();
	void setup_toolbar();
	void connect_signals();
	void init_values();

	shared_ptr<channels::BaseChannel> channel_;
	data::BaseCurve *curve_;

	QAction *const action_add_marker_;
	QAction *const action_add_diff_marker_;
	QAction *const action_zoom_best_fit_;
	QAction *const action_config_plot_;
	QToolBar *toolbar_;
	widgets::Plot *plot_;

private Q_SLOTS:
	void on_signal_changed();
	void on_action_add_marker_triggered();
	void on_action_add_diff_marker_triggered();
	void on_action_zoom_best_fit_triggered();
	void on_action_config_plot_triggered();

};

} // namespace views
} // namespace sv

#endif // VIEWS_PLOTVIEW_HPP

