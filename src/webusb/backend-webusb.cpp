// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2015 Intel Corporation. All Rights Reserved.

#include "backend-webusb.h"
#include "backend.h"
#include "types.h"
#include "usb/usb-enumerator.h"
#include "usb/usb-device.h"

namespace librealsense
{
    namespace platform
    {
		class webusb_device_watcher : public device_watcher
		{
		public:
			void start(device_changed_callback callback) {}
			void stop() {}
			~webusb_device_watcher() {};
		};

		rs_usb_device usb_enumerator::create_usb_device(const usb_device_info& info)
		{
			return nullptr;
		}

		std::vector<usb_device_info> usb_enumerator::query_devices_info()
		{
			std::vector<usb_device_info> rv;
			return rv;
		}

		std::shared_ptr<uvc_device> webusb_backend::create_uvc_device(uvc_device_info info) const {
			return nullptr;
		}

		std::vector<uvc_device_info> webusb_backend::query_uvc_devices() const {
			std::vector<uvc_device_info> uvc_nodes;
			return uvc_nodes;
		}

		std::shared_ptr<command_transfer> webusb_backend::create_usb_device(usb_device_info info) const {
			auto dev = usb_enumerator::create_usb_device(info);
			if (dev)
				return std::make_shared<platform::command_transfer_usb>(dev);
			return nullptr;
		}

		std::vector<usb_device_info> webusb_backend::query_usb_devices() const {
			std::vector<usb_device_info> usb_nodes;
			return usb_nodes;
		}

		std::shared_ptr<hid_device> webusb_backend::create_hid_device(hid_device_info info) const {
			return nullptr;
		};

		std::vector<hid_device_info> webusb_backend::query_hid_devices() const {
			std::vector<hid_device_info> hid_nodes;
			return hid_nodes;
		}

		std::shared_ptr<time_service> webusb_backend::create_time_service() const {
			//return nullptr;
			return std::make_shared<os_time_service>();
		}

		std::shared_ptr<device_watcher> webusb_backend::create_device_watcher() const {
			//return nullptr;
			//return std::make_shared<polling_device_watcher>(this);
			return std::make_shared<webusb_device_watcher>();
		}
	
        std::shared_ptr<backend> create_backend()
        {
            return std::make_shared<webusb_backend>();
        }
    }
}
