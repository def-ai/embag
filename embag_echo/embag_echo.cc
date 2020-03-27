#include <iostream>
#include <vector>
#include <boost/program_options.hpp>

#include "lib/embag.h"

int main(int argc, char *argv[]) {
  namespace po = boost::program_options;

  po::options_description desc("Usage:");
  desc.add_options()
    ("help", "produce help message")
    ("topic,t", po::value<std::vector<std::string> >(), "topic to echo")
    ("bag,b", po::value<std::vector<std::string> >(), "bag files to read")
    ;

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.count("help")) {
    std::cout << desc << std::endl;
    return 0;
  }

  if (vm.count("bag") == 0) {
    std::cout << "You must specify at least one bag file." << std::endl;
    return 1;
  }

  Embag::View view{};

  for (const auto& filename : vm["bag"].as<std::vector<std::string>>()) {
    std::cout << "Opening " << filename << std::endl;
    auto bag = std::make_shared<Embag::Bag>(filename);
    view.addBag(bag);
  }

  if (vm.count("topic")) {
    for (const auto &message : view.getMessages(vm["topic"].as<std::vector<std::string>>())) {
      std::cout << message->timestamp.secs << "." << message->timestamp.nsecs << " : " << message->topic << std::endl;
      message->print();
    }
  } else {
    for (const auto &message : view.getMessages()) {
      std::cout << message->timestamp.secs << "." << message->timestamp.nsecs << " : " << message->topic << std::endl;
      message->print();
    }
  }

  return 0;
}
