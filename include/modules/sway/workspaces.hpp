#pragma once

#include <fmt/format.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include "IModule.hpp"
#include "bar.hpp"
#include "client.hpp"
#include "modules/sway/ipc/client.hpp"
#include "util/json.hpp"
#include "util/sleeper_thread.hpp"

namespace waybar::modules::sway {

class Workspaces : public IModule {
 public:
  Workspaces(const std::string&, const waybar::Bar&, const Json::Value&);
  ~Workspaces() = default;
  auto update() -> void;
       operator Gtk::Widget&();

 private:
  void              onCmd(const struct Ipc::ipc_response);
  void              worker();
  void              addWorkspace(const Json::Value&);
  void              onButtonReady(const Json::Value&, Gtk::Button&);
  std::string       getIcon(const std::string&, const Json::Value&);
  bool              handleScroll(GdkEventScroll*);
  const std::string getCycleWorkspace(const Json::Value& workspaces, uint8_t current,
                                      bool prev) const;
  uint16_t          getWorkspaceIndex(const Json::Value& workspaces, const std::string& name) const;
  std::string       trimWorkspaceName(std::string);
  const Json::Value getWorkspaces();

  const Bar&                                   bar_;
  const Json::Value&                           config_;
  Json::Value                                  workspaces_;
  waybar::util::SleeperThread                  thread_;
  Gtk::Box                                     box_;
  util::JsonParser                             parser_;
  Ipc                                          ipc_;
  std::mutex                                   mutex_;
  bool                                         scrolling_;
  std::unordered_map<std::string, Gtk::Button> buttons_;
};

}  // namespace waybar::modules::sway
