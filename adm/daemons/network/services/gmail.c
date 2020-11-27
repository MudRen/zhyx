/*
 * File    : gmail.c
 * Creator : smallfish@vip.sina.com
 * When    : 2002-12-07
 *
 * This file is part of the tmi mudlib.  Please keep this header intact.
 *
 * This protocol is used to convey intermud mailbox.
 */

// Ported to HUAXIA mudlib by Smallfish (2002-12-07)

#include <command.h>
#include <net/dns.h>
#include <net/macros.h>
#include <net/daemons.h>
#include <getconfig.h>

inherit F_CLEAN_UP;
inherit F_DBASE;

// Tell to someone on another mud.

int send_gmail(string mud, string wiz_to, object source, mapping mail)
{
        mapping minfo;

        if (strsrch(base_name(previous_object()), "/clone/misc/mailbox") != 0)
                return 0;

        if (!source)
                return 0;

        mud = htonn(mud);
        if (mud == mud_nname() || ! source) return 0;

        minfo = (mapping)DNS_MASTER->query_mud_info(mud);
        if (! minfo)
        {
                tell_object(source, LOCAL_MUD_NAME() + "��û�к� " + mud + " ��ϵ�ϡ�\n");
                return 0;
        }


        mail["text"] = replace_string(mail["text"], "|", "");
        mail["text"] = replace_string(mail["text"], "@@@", "");
        DNS_MASTER->send_udp(minfo["HOSTADDRESS"], minfo["PORTUDP"],
                "@@@" + DNS_GMAIL +
                "||NAME:" + Mud_name() +
                "||FROM:" + mail["from"] +
                "||PORTUDP:" + udp_port() +
                "||WIZTO:" + wiz_to +
                "||WIZFROM:" + capitalize(source->query("id")) +
                "||CNAME:" + source->name(1) +
                "||WIZ_LEVEL:" + wiz_level(source) +
                "||TITLE:" + mail["title"] +
                "||MSG:" + mail["text"] + "@@@\n");
        return 1;
}

// Someone on another mud has sent us a tell.
void incoming_request(mapping info)
{
        mapping minfo;
        object pl,mbx;
        mapping mail = ([]);
        string reply;

        if (info["NAME"] && info["PORTUDP"])
        {
                // dont want to tell to ourselves
                if (info["NAME"] == Mud_name()) return;

                // get our info about the sender, ping them if we don't have any
                minfo = DNS_MASTER->query_mud_info(info["NAME"]);
                if (! minfo || ! DNS_MASTER->dns_mudp(info["NAME"]))
                        PING_Q->send_ping_q(info["HOSTADDRESS"], info["PORTUDP"]);

                if (minfo && minfo["HOSTADDRESS"] != info["HOSTADDRESS"])
                {
                        // Its been faked! 
                        dns_log("dns_fake", "GMAIL: " + info["WIZFROM"] + "@" + info["NAME"] +
                                "("+info["HOSTADDRESS"] + ") mail " + info["WIZTO"] +
                                " " + info["MSG"] + "\n");
                        DNS_MASTER->send_udp(minfo["HOSTADDRESS"], minfo["PORTUDP"],
                                "@@@" + DNS_WARNING +
                                "||MSG: Faked gmail message " + info["WIZFROM"]+
                                "@" + info["NAME"] + "> " + info["WIZTO"]+
                                " " + info["TITLE"] + "---" + info["MSG"] +
                                "||FAKEHOST:" + info["name"]+
                                "@@@\n");
                        return ;
                }

                mail["from"] = info["FROM"];
                mail["title"] = info["TITLE"];
                mail["to"] = info["WIZTO"];
                mail["time"] = time();
                mail["text"] = info["MSG"];

                mbx = new(MAILBOX_OB);
                reply = mbx->remote_mail(mail["to"],info["WIZTO"]+"@"+Mud_name(),mail);
                destruct(mbx);
        
                (AUX_PATH + "affirmation_a")->send_affirmation_a(info["HOSTADDRESS"],
                        info["PORTUDP"], "Gtell@" + Mud_name(),
                        info["WIZFROM"], reply, "gtell");
        }
}

