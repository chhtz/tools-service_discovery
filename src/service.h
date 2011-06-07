/*
 * Service.h
 *
 *  Created on: Mar 17, 2010
 *      Author: darko
 */

#ifndef _SERVICE_DISCOVERY_SERVICE_H_
#define _SERVICE_DISCOVERY_SERVICE_H_

#include <string>
#include <list>
#include <iostream>
#include <avahi-client/lookup.h>
#include <avahi-client/client.h>
#include <service_discovery/client.h>
#include <service_discovery/service_configuration.h>

namespace servicediscovery {
class Service;
class Client;
}

namespace servicediscovery {

class Service {
protected:
	/**
	 * port of the service
	 */
	uint16_t port;
	
        /** private avahistringlist instance */
	AvahiStringList *txt;
	
        /** the list of string correspondent of avahistringlist */
	std::list<std::string> stringlist;
	
	static AvahiStringList* getTxt(std::list<std::string>);
	
	void setTxt(AvahiStringList* ntxt) {
		if (txt) {
			avahi_string_list_free(txt);
		}
		txt = ntxt;
	}

        /** related avahi client instance */
        Client* client_;

        /** Current ServiceConfiguration for this service */
        ServiceConfiguration configuration_;

        void addDescriptionsToConfiguration(const std::list<std::string>& strlist);
	
	
public:

	bool dontCheckTXT;

	Service(const Service&);

	Service(Client *client, AvahiIfIndex interf, AvahiProtocol prot, std::string name, 
                std::string type, std::string domain, uint16_t port = 0, 
                std::list<std::string> list = std::list<std::string>());

	virtual ~Service();

	bool operator==(const Service&);

        uint16_t getPort() const { return port; }

        AvahiStringList *getTxt() const { return txt; }

        std::list<std::string> getStringList() const { return stringlist; }

        std::string getName() const { return configuration_.getName();}

        void setConfiguration(const ServiceConfiguration& config);

        ServiceConfiguration getConfiguration() const;

        Client* getClient();
};

} // end namespace servicediscovery

#endif /* _SERVICE_DISCOVERY_SERVICE_H_ */
