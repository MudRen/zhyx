/// who.c
// Modified by Yu Jue@JY
// Modify by Yu Jue@SJ 1999-06-24
// Modified by Numa@Sj 1999-11-18 ÃÅÅÉÖØĞÂÅÅÁĞ (²»×¼¸²¸ÇÁË£¬ bite. 4.23.2000)
// Modified by snowman@SJ 14/11/2000.  Íæ¼Ò°´ÓÎÏ·Ê±¼äÅÅÁĞ¡£
// Modified by Looklove@SJ Ôö¼Ó²é¿´ÔÚÏß¹¤½³¹¦ÄÜ
inherit F_CLEAN_UP;

#include <ansi.h>
#include <mudlib.h>
#include <net/dns.h>

mapping party=([
        "emei":         "¶ëáÒÅÉ",
        "zaixian":      "ÔÚÏßÈËÔ±",
        "gaibang":      "Ø¤°ï",
        "gumu":         "¹ÅÄ¹ÅÉ",
        "huashan":      "»ªÉ½ÅÉ",
        "kunlun":       "À¥ÂØÅÉ",
        "mingjiao":     "Ã÷½Ì",
        "murong":       "¹ÃËÕÄ½Èİ",
        "quanzhen":     "È«Õæ½Ì",
        "shaolin":      "ÉÙÁÖÅÉ",
        "shenlong":     "ÉñÁú½Ì",
        "songshan":     "áÔÉ½ÅÉ",
        "taohua":       "ÌÒ»¨µº",
        "tianlong":     "ÌìÁúËÂ",
        "tiezhang":     "ÌúÕÆ°ï",
        "wudang":       "Îäµ±ÅÉ",
        "xingxiu":      "ĞÇËŞÅÉ",
        "xueshan":      "´óÂÖËÂ",
        "lingjiu":      "ÁéğÕ¹¬",
        "xiaoyao":      "åĞÒ£ÅÉ",
        "riyue":        "ÈÕÔÂÉñ½Ì",
        "ouyang":       "Å·ÑôÊÀ¼Ò",
]);

int sort_user(object,object);

void create() {
        string *pname = values(party);
        int i = sizeof(pname);

        seteuid(getuid());
        while (i--) party[pname[i]] = pname[i];
}

string opt_party;

void remove_busy(object me)
{
        if( me)delete_temp("command_busy", me);
}

mixed main(object me, string arg, int remote)
{
        string str, *option, fname = "";
        object *list;
        int i, ppl_cnt, cnt, count, wcnt = 0;
        int opt_long, opt_id, opt_wiz, opt_wizall, opt_career, opt_zhuanzhan;

        if (!remote) {
                if( query_temp("command_busy", me) )
                        return notify_fail("ÄãÕıÃ¦×ÅÄØ¡£\n");
set_temp("command_busy", 1,             me);
                call_out("remove_busy", 3, me);
        }

        opt_party = "(null)";

        if( arg ) {
                option = explode(arg, " ");
                option -= ({ "" });
                i = sizeof(option);
                while( i-- )
                        switch(option[i]) {
                                case "-l": opt_long = 1; break;
                                case "-i": opt_id = 1; break;
                                case "-wizall": opt_wizall = 1;
                                case "-w": opt_wiz = 1; break;
                                case "-c": opt_career = 1; break;
                                case "-z": opt_zhuanzhan = 1; break;
                                case "-f":
                                case"-p":opt_party=query("family/family_name", me);break;
                                default:
                                        if( option[i][0]=='@' ) {
                                                notify_fail("ÍøÂ·¾«Áé²¢Ã»ÓĞ±»ÔØÈë¡£\n");
                                                if (find_object(DNS_MASTER) && RWHO_Q->send_rwho_q(option[i][1..<1],
                                                        me, opt_long & wizardp(me), opt_wiz, opt_party )) {
                                                        // Ö»ÓĞ¹¤×÷ÈËÔ±²ÅÔÊĞí who @xx -l£¬Yu Jue@SJ 19990624
                                                        write("ÍøÂçÑ¶Ï¢ÒÑËÍ³ö£¬ÇëÉÔºò¡£\n");
                                                        return 1;
                                                return 0;
                                        }
                                        if (option[i][0] == '-' && !undefinedp(party[option[i][1..<1]]))
                                                opt_party = party[option[i][1..<1]];
                                        else return notify_fail("Ö¸Áî¸ñÊ½£ºwho [-l|-i|-w|-p|-c]\n");
                        }
        }
/*
        if (!remote && opt_wizall && find_object(DNS_MASTER)) {
                string *mud = sort_array(keys(DNS_MASTER->query_muds()), -1);
                int m = sizeof(mud);

                while (m--) RWHO_Q->send_rwho_q(mud[m], me, 0, 1, opt_party);
        }
*/
        if( opt_long && !remote && !wizardp(me)) {
                if( query("jing", me)<50 )
                        return notify_fail("ÄãµÄ¾«ÉñÌ«²îÁË£¬Ã»ÓĞ°ì·¨µÃÖªËùÓĞÍæ¼ÒµÄÏêÏ¸×ÊÁÏ¡£\n");
                me->receive_damage("jing", 50);
        }

        str = "¡ò " + CHINESE_MUD_NAME + (opt_party == "(null)"?"":opt_party)
                + "ÔÚÏß" + (opt_wiz?"¹¤×÷ÈËÔ±":opt_career?"¹¤½³":opt_zhuanzhan?"×ªÕ¾ÈËÔ±":"Íæ¼Ò") + "£º\n";
        str += repeat_string("©¥", 40) + "\n";
        list = filter_array(children(USER_OB), (: userp($1) && environment($1) :));
        if (opt_party != "(null)")
                list=filter_array(list,(:query("family/family_name", $1) == 
                        opt_party :));
        if ( opt_career )
                list=filter_array(list,(:query_temp("user_type", $1) == "worker":));
        if ( opt_zhuanzhan && wizardp(me) )
                list=filter_array(list,(:query("bxsj_bonus/oldsj", $1):));

        list = sort_array(list, (: sort_user :));
        ppl_cnt = 0;
        cnt = 0;
        if( opt_long || opt_wiz ) {
                i = sizeof(list);
                while( i-- ) {
                        if( remote && wizardp(list[i]) && query("env/invisibility", list[i]))continue;
                        if (!remote && !me->visible(list[i]) ) continue;
                        if (opt_wiz && !wizardp(list[i]) ) continue;
                        if (interactive(list[i])) ppl_cnt++;
                        else cnt++;
                        if( !wiz_level(list[i]) && fname != query("family/family_name", list[i]) )
                                fname=query("family/family_name", list[i]);
                        if (!wcnt && wiz_level(list[i])) {
                            wcnt = 1;
                        }
                        str += sprintf("%12s%s%s\n",
                                RANK_D->query_rank(list[i]),
                                interactive(list[i])?
                                        (query_idle(list[i]) > 120?HIM"+"NOR:" ")
                                        :HIG"*"NOR,
                                list[i]->short(1)
                        );
                }
        } else {
                string name;

                i = sizeof(list);
                count = 0;
                while( i-- ) {
                        // Skip those users in login limbo.
                        if( remote && wizardp(list[i]) && query("env/invisibility", list[i]))continue;
                        if (!remote && !me->visible(list[i])) continue;
                        if( !wiz_level(list[i]) && fname != query("family/family_name", list[i])){
                                fname=query("family/family_name", list[i]);
                                if (count % (opt_id?4:8)) str += "\n";
                                str += sprintf(HIY "%-*s" NOR, opt_id?20:10, (fname?fname:"ÆÕÍ¨°ÙĞÕ") + "£º");
                                count = 1;
                        }
                        if (!wcnt && wiz_level(list[i])) {
                                if (count % (opt_id?4:8)) str += "\n";
                                str += sprintf(HIY "%-*s" NOR, opt_id?20:10, "¹¤×÷ÈËÔ±£º");
                                wcnt = 1;
                                count = 1;
                        }
                        name = query("name",list[i]) + (opt_id ? "("+capitalize(query("id",list[i]))+")" : "");
                        str += sprintf(" %-*s%s",
                                opt_id?19:9,
                                interactive(list[i])?
                                        (query_idle(list[i]) > 120 ? HIM"+"+name+NOR : " "+name)
                                        : HIG"*"+name+NOR,
                                ++count % (opt_id?4:8) ? "" : "\n"
                        );
                        if (interactive(list[i])) ppl_cnt++;
                        else cnt++;
                }
                if( count % (opt_id?4:8) ) str += "\n";
        
        str += repeat_string("©¥", 40) + "\n"
        str += sprintf
                "ÓĞ %d Î»%sÁ¬ÏßÖĞ£¬%d Î»%s¶ÏÏßÖĞ£¬"HIG"*"NOR" ±íÊ¾¶ÏÏßÖĞ  "HIM"+"NOR" ±íÊ¾·¢´ôÖĞ\n"
                ppl_cnt, opt_wiz?"¹¤×÷ÈËÔ±":"Íæ¼Ò", cnt, opt_wiz?"¹¤×÷ÈËÔ±":"Íæ¼Ò", query_load_average(
        )
        if( remote ) return str
        me->start_more(str)
        return 1
int sort_user(object ob1, object ob2
        string name1, name2
        int l1 = wiz_level(ob1), l2 = wiz_level(ob2)
        if (l1 != l2) return l2 - l1
        if (l1) 
                name1=query("id", ob1)
                name2=query("id", ob2)
                if (intp(name1)) name1 = ""
                if (intp(name2)) name2 = ""
                if (name1 > name2) return -1
                if (name1 < name2) return 1
                return 0
        
        reset_eval_cost()
        name1=query("family/family_name", ob1)
        name2=query("family/family_name", ob2)
        if (intp(name1)) name1 = ""
        if (intp(name2)) name2 = ""
        if (name1 > name2) return -1
        if (name1 < name2) return 1
        l1=query("family/generation", ob1)
        l2=query("family/generation", ob2)
        if (l1 != l2) return l1 - l2
        // sort by playing time
        return query("online_total", ob2) - query("online_total", ob1)
        //query("combat_exp", return ob2)-query("combat_exp", ob1)
int help(object me
        string *p
        int i,j
        write(@HEL
Ö¸Áî¸ñÊ½ : who [-l|-i|-w|-p|-c|-Ó¢ÎÄ´úºÅ
Õâ¸öÖ¸Áî¿ÉÒÔÁĞ³öËùÓĞÔÚÏßÉÏµÄÍæ¼Ò¼°ÆäµÈ¼¶¡
-l Ñ¡ÏîÁĞ³ö½Ï³¤µÄÑ¶Ï¢¡
-i Ö»ÁĞ³öÍæ¼ÒµÄÓ¢ÎÄ´úºÅ¡
-p Ö»ÁĞ³öÍ¬ÃÅµÄÍæ¼Ò¡
-f Í¬É
-w Ö»ÁĞ³öÏßÉÏËùÓĞµÄ¹¤×÷ÈËÔ±¡
-c Ö»ÁĞ³öÔÚÏß¹¤½
-Ó¢ÎÄ´úºÅ Ö»ÁĞ³ö¸ÃÃÅÅÉµÄÍæ¼Ò¡
HELP)
        p = sort_array(keys(party), 1)
        i = sizeof(p)
        j = i
        write(sprintf("   %-12s%-12s    %-12s%-12s\n","Ó¢ÎÄ´úºÅ","ÃÅÅÉÃû","Ó¢ÎÄ´úºÅ","ÃÅÅÉÃû"))
        write("----------------------------------------------------------\n")
        for (i=0;i<j/2;i++
        
                if (i==(j/2-1)
                
                        write(sprintf("   %-10s£º%-12s\n", p[i], party[p[i]]))
                        continue
                
                if (i/2*2==i
                        write(sprintf("   %-10s£º%-12s|", p[i], party[p[i]]))
                els
                        write(sprintf("   %-10s£º%-12s\n", p[i], party[p[i]]))
        
        write("----------------------------------------------------------\n")
        write(@HEL
Ïà¹ØÖ¸Áî£º finge
HELP)
        return 1
