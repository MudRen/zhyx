/*
 * File    : reboot_q.c
 * Creator : xdie@SDXL
 * When    : 03-10-23
 *
 *
 * This protocol is used to reboot a mud.
 */


#include <net/dns.h>
#include <net/macros.h>

inherit F_CLEAN_UP;

// Some mud or other has decied to tell us to shut down...
void incoming_request(mapping info)
{
        mapping mud_info;

        if(!ACCESS_CHECK(previous_object())) return;

        if(!info["NAME"])
                return;

        mud_info = (mapping)DNS_MASTER->query_mud_info(info["NAME"]);
                if(!mud_info || !DNS_MASTER->dns_mudp(info["NAME"]))
                        return;

        if(info["HOSTADDRESS"] != mud_info["HOSTADDRESS"])
        { // faked
        dns_log("dns_fake", sprintf("Shutdown from: %s for %s (%s) @%s\n",
                                mud_info["HOSTADDRESS"], info["NAME"],
                                info["HOSTADDRESS"], ctime(time()) ));
        DNS_MASTER->send_udp(mud_info["HOSTADDRESS"],
                           atoi(mud_info["PORTUDP"]),
                           "@@@"+DNS_WARNING+
                           "||MSG: Faked shutdown message from "+
                           info["HOSTADDRESS"] + "||FAKEHOST:" +
                           info["NAME"] + "@@@");
        return;
        }

        message("system", "ϵͳ����Զ�̲������������������Ժ������ӡ�\n", users());
        log_file("static/CRASHES", sprintf("%s(%s) remote reboot from %s at %s", 
                info["CNAME"], info["WIZFROM"], info["HOSTADDRESS"], ctime(time())[0..15]));

        DNS_MASTER->send_shutdown();
        shutdown(0);
}

void create()
{
  seteuid(ROOT_UID);
}

