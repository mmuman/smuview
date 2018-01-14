/*
 * This file is part of the SmuView project.
 *
 * Copyright (C) 2017 Frank Stettner <frank-stettner@gmx.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <list>
#include <map>
#include <memory>
#include <string>

#include <QToolBar>
#include <QToolBox>
#include <QToolButton>
#include <QStatusBar>
#include <QMainWindow>

using std::list;
using std::map;
using std::shared_ptr;
using std::string;

namespace sv {

class DeviceManager;
class Session;

namespace devices {
class Device;
class HardwareDevice;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(DeviceManager &device_manager,
		QWidget *parent = 0);

    ~MainWindow();

	void init_session();
	void init_default_session();
	void init_session_with_file(string open_file_name, string open_file_format);
	void save_session();
	void restore_session();
	void remove_session();

	shared_ptr<devices::Device> add_tab(
		shared_ptr<devices::HardwareDevice> device);
	void remove_tab(shared_ptr<devices::HardwareDevice> device);

private:
	void setup_ui();
	void connect_signals();
	void retranslate_ui();
	void session_error(const QString text, const QString info_text);

	DeviceManager &device_manager_;
	shared_ptr<Session> session_;

	shared_ptr<devices::Device> last_focused_device_;
	map<shared_ptr<devices::Device>, QMainWindow*> device_windows_;

	QToolButton *add_device_button_;
	QToolButton *add_user_tab_button_;
	QWidget *centralWidget;
	QToolBox *infoWidget;
	QTabWidget *tab_widget_;
	QWidget *static_toolbar_;
	QStatusBar *statusBar;

private Q_SLOTS:
	void show_session_error(const QString text, const QString info_text);
	void on_action_add_device_triggered();
	void on_action_add_user_tab_triggered();

};

} // namespace sv

#endif // MAINWINDOW_HPP
