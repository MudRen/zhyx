// ultraquestd.c
// Written by Vin for Heros.cn 2002/08/16.
// Updated by Lonely for nitan.nt
            
#include <ansi.h> 
#include <quest.h> 
 
inherit F_DBASE; 

// �����ṩ���ⲿ���õĽӿں��� 
public mixed accept_ask(object me, object who, string topic); 
public mixed ask_information(object me, object who, string topic); 
public void generate_information(object me); 
public void give_quest(object me); 
public void give_accede(object me, object who); 
public void quest_guard(object me, object who); 
public void quest_going(object me, object who); 
public void give_gift(object me); 
void start_guard(object me, object who); 
void check_guard(object me, object who, object killer); 
void check_going(object me, object who); 
   
#define QUEST           "/adm/etc/questlist/" 
#define OBJ_DIR         "/quest/questobj/" 
#define NPC_DIR         "/quest/questnpc/"
#define QUESTER "����" 
#define LURCHER "����" 
 
private void special_bonus(object me) 
{ 
        object ob; 
        string un; 

        // �����������Ʒ������ 
        string *ob_list = ({ 
                "/clone/fam/etc/hanjing", 
                "/clone/fam/etc/mozhixin",
                "/clone/fam/item/bless_water",
                "/clone/fam/etc/huojingling",
                "/clone/fam/etc/leishentong",
                "/clone/fam/max/zhenyu",
                "/clone/fam/max/longjia",
                "/clone/fam/max/xuanhuang",
                "/clone/fam/pill/dimai",
                "/clone/fam/pill/yulu",
                "/clone/fam/pill/renshen4",
                "/clone/fam/pill/lingzhi4",
                "/clone/fam/pill/xuelian4",
                "/clone/fam/pill/renshen3",
                "/clone/fam/pill/lingzhi3",
                "/clone/fam/pill/xuelian3",
                "/clone/fam/pill/linghui2",
                "/clone/fam/pill/neili2",
                "/clone/fam/pill/puti4",
                "/clone/fam/pill/sheli4",
                "/clone/fam/pill/sheli3",
                "/clone/fam/pill/puti3",
                "/clone/fam/pill/puti2",
                "/clone/fam/pill/sheli2",        
                "/clone/fam/max/xuanhuang",
        }); 
        
        ob = new(ob_list[random(sizeof(ob_list))]); 
        
        // �鿴��Ʒ�ĵ�λ���� 
        if (ob->query("base_unit")) 
                un = ob->query("base_unit"); 
        else 
                un = ob->query("unit"); 
                               
        // ������������ give ��Ϣһ�� 
        message_vision("˵���ó�һ" + 
                       un + ob->name() + NOR "(" + ob->query("id") + 
                       ")��$N" NOR "��\n\n" NOR, me); 
        
        ob->move(me, 1); 
} 
        
// �������ʼ���򣬸�������������ṩ������ 
public mixed accept_ask(object me, object who, string topic) 
{
        object item, obj; 
        string msg, file, name, id; 
        mapping q; 
        string *ob;

        q = who->query("ultraquest/");        
        if (topic == "����" || topic == "quest") 
        {
                message_vision("$n��$N�����й���ʦ����������\n", me, who);
                /*
                if (! ultrap(who)) 
                {
                        message_vision("$N�ɴ��۾�����$n���������㻹û�г�Ϊ��ѧ����ʦ�����ﲻ��"
                                       "��ʲôæ����\n", me, who);
                        return 1;
                }
                */
                                                        
                if (mapp(q)) 
                {
                        switch (q["type"]) 
                        { 
                        case "find":   // Ѱ��
                                message_vision(CYN "$N" CYN "һ��ŭ�ݶ�$n" CYN "�����Ҳ�����" 
                                               "���" NOR + HIR + q["name"] + "(" + q["id"] + 
                                               ")" + NOR + CYN "����������������������أ�\n" NOR, 
                                               me, who);   
                                break;
                        case "send":   // ����
                                message_vision(CYN "$N" CYN "һ��ŭ�ݶ�$n" CYN "�����Ҳ�����"
                                               "��Ѱ����͸�" NOR + HIR + q["name"] + "(" + q["id"] + 
                                               ")" + NOR + CYN "�������ڻ�ִ�أ�\n" NOR, 
                                               me, who);   
                                break;
                        case "rescue": // ����
                                message_vision(CYN "$N" CYN "һ��ŭ�ݶ�$n" CYN "�����Ҳ�����"
                                               "��ȥ��" NOR + HIR + q["name"] + "(" + q["id"] + 
                                               ")" + NOR + CYN "��ȳ��������������أ�\n" NOR, 
                                               me, who);                                   
                                break;
                                  
                        case "kill":   // ɱ��
                                message_vision(CYN "$N" CYN "һ��ŭ�ݶ�$n" CYN "�����Ҳ�����" 
                                               "��ȥ�����𽭺��ȷ�Ѫ���Ļ����ı����������"
                                               "����ͷ�أ�\n" NOR, me, who);
                                break;
        
                        } 
                        return 1;
                }                                             
                
                if (who->query("combat_exp") < 8000000) 
                { 
                        message_vision(CYN "$N" CYN "̾��һ��������$n" CYN "���������ǵ�ˮƽ��" 
                                       "��ʵ��û������������\n" NOR, me, who); 
                        return 1; 
                } 

                if (who->query("score") < 100000) 
                {
                        message_vision(CYN "$N" CYN "̾��һ��������$n" CYN "��������������̫�ͣ�"
                                       "��ͨ�������ﲻ����ʲôæ��\n" NOR, me, who); 
                        return 1;                 
                }

                if (who->query("weiwang") < 200) 
                { 
                        message_sort(CYN "$N" CYN "���˿�$n" CYN "��̾����������" 
                                     "������һ����ͷ��û�У���û�����İ����񽻸�" 
                                     "�㡣\n" NOR, me, who); 
                        tell_object(who, HIY "�������ǵļ�ǿ�Լ��Ľ����������С�\n" NOR); 
                        return 1; 
                } 
                /*
                if (who->is_bad() && me->is_good())
                {
                        message_sort(CYN "$N" CYN "��ŭ�������д������Ȼ�Ѿ���" 
                                     "����;�����������ң�\n" NOR, me, who); 
                        return 1; 
                } 
        
                if (who->is_good() && me->is_bad())
                {
                        message_sort(CYN "$N" CYN "��ŭ�������д����ż��첻����" 
                                     "���ȻҲѧ����ʼ������ˣ�����ҹ���\n" 
                                     NOR, me, who); 
                        return 1; 
                } 
                */
                
                who->delete("ultraquest");       
                // ����ԭ����������������ͣ�������Ϊһ������                 
                switch (random(4)) 
                {
                case 0:                                     
                        message_sort(CYN "$N" CYN "������$n" CYN "��ã����ŵ�ͷ�������ڽ�"
                                     "�����岻�죬а�����У��ȷ�Ѫ�겻�ϣ���˵��һ�ж�����"
                                     "���ڲ��ݣ������ȥ��������ı��˭��������ͷ­������"
                                     "��\n" NOR, me, who);
                        break;
                case 1: 
                        message_sort(CYN "$N" CYN "��$n" CYN "��������������������ش���"
                                     "����ʱ�����ȷ�Ѫ�꣬�ⱳ��϶����˲��ݣ������ȥ���"
                                     "Ļ����ı��������ͷ­�����ҡ�\n" NOR, me, who);
                        break;
                case 2: 
                        message_sort(CYN "$N" CYN "��$n" CYN "������˵��һ���������ڲ߻���"
                                     "�����������ȷ�Ѫ�꣬��ͼ�߸����֣������ȥ���Ļ����"
                                     "ı��˭����������ͷ�����ҡ�\n" NOR, me, who);
                        
                        break;
                case 3:
                        /*
                        ob = get_dir(NPC_DIR, 0);
                        file = NPC_DIR + ob[random(sizeof(ob))];  
                        who->set("ultraquest/type", "kill");   
                        who->set("ultraquest/file", file); 
                        obj = new(file);
                        name = obj->query("name");
                        id = obj->query("id");
                        who->set("ultraquest/name", name);
                        who->set("ultraquest/id", id);  
                        destruct(obj);
                        */
                        message_sort(CYN "$N" CYN "��$n" CYN "����������������ȷ�Ѫ�꣬��"
                                     "���ɱ���һ������ı����ȥ���Ҳ��������ı��˭��������"
                                     "ͷ­�����ҡ�\n" NOR, me, who);
                        break;  
                }
                
                who->set("ultraquest/type", "kill");    
                // ִ���ṩ�����ĳ��򣬱���Ԥ���趨�ṩ�� 
                who->set("ultraquest/npc1", me->query("id")); 
                who->set("ultraquest/name1", me->query("name"));
                
                generate_information(who); 
                return 1; 
        } 
        
        if (topic == "����" || topic == "clue") 
        {
                if (! who->query("ultraquest/type")) 
                        return "��Ҫ��ʲô�£�˵���������׵ġ�"; 
        
                if (who->query("ultraquest/finish") == 4) 
                        return "�������Ѿ���������𣿻���Ҫʲô������"; 
        
                // ���ֻ�������ṩ�������� 
                if (who->query("ultraquest/begin") >= 3) 
                        return "�²�������ʣ�µ��������Լ���취�����"; 
        
                switch (who->query("ultraquest/begin")) 
                { 
                case 0: 
                        msg = "������ǵ�һ�Σ�ϣ�����������»ء�"; 
                        break; 
        
                case 1: 
                        msg = "���Ѿ������һ���ˣ�����ǵڶ��Ρ�"; 
                        break; 
        
                default: 
                        msg = "���Ѿ������һ���ˣ���������Ϊ֮��"; 
                        break; 
                } 
        
                message_sort(WHT "\n$N" WHT "������ü����$n" WHT "���������������"
                             "������ʵ��һ�������Ĺ��̣��ܶ�ط����뾭��ĥ����ƾ��"
                             "�����������������ܰ쵽��������������������԰���"
                             "���Ρ�" + msg + "\n\n" NOR, me, who); 

                // ȡ����ǰ����������                                        
                who->delete("ultraquest/quest");  // ��֧����
                who->delete("ultraquest/gift");   // ��֧������                     
                who->delete("ultraquest/finish"); // ��֧���������
                who->delete("ultraquest/npc1");   // ��һ���� id
                who->delete("ultraquest/name1");  // ��һ���� name
                who->delete("ultraquest/npc2");   // �ڶ����� id
                who->delete("ultraquest/name2");  // �ڶ����� name
                who->delete("ultraquest/npc3");
                who->delete("ultraquest/name3");
                who->delete("ultraquest/npc4");
                who->delete("ultraquest/name4");
                who->delete("ultraquest/npc5");
                who->delete("ultraquest/name5");
                who->delete("ultraquest/place");  // �ṩ��������ĵص�
        
                // ��¼����ѯ�ʵĴ��� 
                who->add("ultraquest/begin", 1); 
        
                // ��¼�ṩ�������������� 
                who->set("ultraquest/npc1", me->query("id")); 
                who->set("ultraquest/name1", me->query("name"));
        
                // �����ṩ���� 
                generate_information(who); 
                return 1; 
        }
        
        if (topic == "ȡ��" || topic == "cancel")  
        {
                   /*
                if (! who->query("ultraquest/type")) 
                        return "��û����ʲô���񰡣�";
                   */
                        
                who->add("weiwang", -50);
                if (who->query("weiwang") < 0)
                        who->set("weiwang", 0);
                 
                who->add("score", -100);
                if (who->query("score") < 0)
                        who->set("score", 0);
                        
                who->delete("ultraquest");
                who->delete("ultra_count");
                message_vision(CYN "$N" CYN "̾���������˿�$n" CYN "���������С�¶��ɲ��ˣ����˰ɡ�\n" NOR, 
                               me, who); 
                tell_object(who, HIR "��Ľ��������ͽ��������ܵ�����ʧ��\n" NOR);
                return 1;
        }
                 
} 
        
// ѯ�����������Ҫ�� /inherit/char/npc.c ���Ӷ�Ӧ���� 
public mixed ask_information(object me, object who, string topic) 
{ 
        string msg; 
        string type, ob; 
        string next_npc, npc_place; 

        if (who->query("ultraquest/npc5"))        
                next_npc = who->query("ultraquest/npc5"); 
        else
        if (who->query("ultraquest/npc4"))  
                next_npc = who->query("ultraquest/npc4"); 
        else
        if (who->query("ultraquest/npc3"))  
                next_npc = who->query("ultraquest/npc3"); 
        else
                next_npc = who->query("ultraquest/npc2"); 
                
        npc_place = who->query("ultraquest/place"); 
        
        if (stringp(type = who->query("ultraquest/quest/type")) &&
            stringp(ob = who->query("ultraquest/quest/name")) &&
            topic == ob) 
        { 
                // �ṩ������������ṩ����������Ϣ�Ľ�� 
                if (me->query("id") == next_npc) 
                { 
                        switch (type) 
                        { 
                        case "kill" : 
                                msg = "���������ҡ��Һ޲��ð�����ʬ��ϣ�"; 
                                break; 
                        /*       
                        case "find" : 
                                msg = "˵�����Ƕ���Ҳ�����ң����Լ�������ɡ�"; 
                                break; 
                        */        
                        case "send" : 
                                msg = "��ʵ������Ҳ���Ǻ��죬���Ĵ�ȥ���ʰɡ�"; 
                                break; 
                        
                        case "give" : 
                                msg = "�Һܾ�û�������ˣ�Ҳ�����������������"; 
                                break; 
                               
                        case "going" : 
                                msg = "�Ҹ���˵�ú�����˰���Ī����Ҳ��ʶ·��"; 
                                break; 
                        } 
                        return msg; 
                } 
        } 
        
        if (topic == "����" || topic == "clue") 
        { 
                // ѯ��Ŀ��Ϊ��һ���ṩ��Ϣ����   
                if (who->query("ultraquest/name5") &&
                    who->query("ultraquest/npc4") == me->query("id")) 
                        return "�Ҳ�������ȥ" + npc_place + "��" HIY + 
                               who->query("ultraquest/name5") + NOR 
                               + CYN "ô����������������" NOR;
               
                if (who->query("ultraquest/name4") &&
                    who->query("ultraquest/npc3") == me->query("id")) 
                        return "�Ҳ�������ȥ" + npc_place + "��" HIY + 
                               who->query("ultraquest/name4") + NOR 
                               + CYN "ô����������������" NOR; 
                                                                                          
                if (who->query("ultraquest/name3") &&
                    who->query("ultraquest/npc2") == me->query("id")) 
                        return "�Ҳ�������ȥ" + npc_place + "��" HIY + 
                               who->query("ultraquest/name3") + NOR 
                               + CYN "ô����������������" NOR;                                
                                                                                                     
                // �����ǰ�������޷�ִ�У����ж� 
                if (who->query("ultraquest/fail")) 
                        return "���鵽����һ������Ҳû���ٰ����ˡ�"; 
        
                // ����Ѿ������������򷵻� 
                if (who->query("ultraquest/quest/msg")) 
                        return "�Ҳ�������" + 
                               who->query("ultraquest/quest/msg") + 
                               "�𣿻�����ʲô��"; 
        
                switch (random(4)) 
                { 
                case 0: 
                        msg = "��Ҫ�ҵ���������ȷʵ֪��һЩ������" 
                              "���ȵð��Ҹ�æ��"; 
                        break; 
        
                case 1: 
                        msg = "������ȷʵ�������֪����üĿ������" 
                              "��Ϣ�ɲ��ܰ׸���"; 
                        break; 
        
                case 2: 
                        msg = "����Ϊһ���·��������ܰ������" 
                              "æ��������Ը����㡣"; 
                        break; 
        
                default: 
                        msg = "���Լ������鶼æ�����������ﻹ�˵�" 
                              "���㣬���������ǡ�"; 
                        break; 
                } 
                message_vision(CYN "$N" CYN "ҡͷ����" + msg + "\n" 
                               NOR, me, who); 
        
                // �����������Ҫ��ִ�м������������ 
                if (me->query("combat_exp") >= 100000 
                    && me->query("age") >= 20 
                    && ! me->query_temp("need_accede") 
                    && random(3) == 1) 
                { 
                        give_accede(me, who); 
                        return 1; 
                } 
        
                // �����������Ҫ��ִ�б����������� 
                if (who->query("combat_exp") > me->query("combat_exp") * 2 / 3 
                    && ! environment(who)->query("no_fight") 
                    && ! me->query_temp("start_guard") 
                    && random(3) == 1) 
                { 
                        /*
                        if (random(2) == 1) 
                        { 
                                // ִ�л��͵����� 
                                quest_going(me, who); 
                                return 1; 
                        } else 
                        { 
                        */
                                // ִ�б��������� 
                                quest_guard(me, who);
                                return 1; 
                        /*
                        } 
                        */
                } 
        
                // ����ϵͳԤ������ 
                give_quest(who); 
                return 1; 
        } 
} 
        
// ����������ķ��� 
public void give_accede(object me, object who) 
{ 
        string msg, type, quest_msg; 
        string skill; 
        string ma, mb, wa, ac; 
        int exp, lvl; 
        
        // ���˳Ƽ������ַ�������д���� 
        ma = RANK_D->query_self(me); 
        mb = RANK_D->query_self_rude(me); 
        wa = RANK_D->query_respect(who); 
        ac = "(" HIY "accede" NOR + WHT ")"; 
        
        switch (random(6)) 
        { 
        case 0: 
                msg = random(2) ? "��λ" + wa + "��" + ma + "�������о�" 
                                  HIW "����" NOR + WHT "�׾��������ĵá�"
                                  "���Ҷ��˱�������" + ac + "һ�̣�����" 
                                  "����ʤ���ҡ���ô" + ma + "��֪������" 
                                  "�������������": 
        
                                  wa + "�������ã�" + mb + "����û������" 
                                  "�������������ұ���" + ac + "һ��" HIW 
                                  "����" NOR + WHT "����������ʤ��������" 
                                  "����ǩ�����̣��Ұ���֪����һ�ж�������"; 
        
                quest_msg = "���ұ�������"; 
                type = "mathematics"; 
                break; 
        
        case 1: 
                msg = random(2) ? "��λ" + wa + "��" + ma + "�������о�" 
                                  HIW "ʫ��" NOR + WHT "�踳���д����" 
                                  "���Ҷ��˱�����ʫ" + ac + "���ԣ�����" 
                                  "���ܶ�Ӯ" + ma + "����ô����֪������" 
                                  "�������������": 
        
                                  "�ҿ�" + wa + "Ҳ����Ҫ�£���Ȼ���Ҷ�" 
                                  "�˶�����ģ���������ʫ" + ac + "��" 
                                  "�ԣ���ͬ̽��̽��" HIW "��ѧ" NOR + WHT 
                                  "֪ʶ������������ʤ�ң�" + ma + "����" 
                                  "������֮"; 
        
                quest_msg = "������ʫ�Զ�"; 
                type = "literate"; 
                break; 
        
        case 2: 
                msg = random(2) ? "��λ" + wa + "��" + ma + "�������о�" 
                                  HIW "����" NOR + WHT "֮���������ĵá�" 
                                  "���Ҷ��˱�������" + ac + "һ�֣�����" 
                                  "����ʤ���ҡ���ô����֪��������������" 
                                  "�����": 
        
                                  wa + "��������ҿ���Ҳû��Ҫ����������" 
                                  "��������ɱ" + ac + "һ��" HIW "��" NOR + 
                                  WHT "��ʡ�����ġ�����������ʤ�Ҽ��ӣ���" 
                                  "���֪����ȫ��������Ҳ�޷�"; 
        
                quest_msg = "������һ����"; 
                type = "chess"; 
                break; 
        
        case 3: 
                msg = random(2) ? "��λ" + wa + "�������ã�" + ma + "��Ϊ" 
                                  "һ�·�������������ѵĴ��٣�" + ma + 
                                  "��������һ�������Ա�ף�أ�������" HIW 
                                  "�鷨" NOR + WHT "����Ƿ�ѣ��������ܰ�" + 
                                  ac + "�Ҵ�������Ը��" + ma + "�м���" 
                                  "��������Ҳ�����������": 
        
                                  wa + "��������ʱ��" + ma + "��Ϊһ��" 
                                  "�������˵������ǰ����һλֿ��Ϊ����" 
                                  "���������Ҳ���������" + ma + "����Ѱ��" 
                                  "һλ" HIW "�鷨" NOR + WHT "����Ϊ����" 
                                  "д���ʣ�ȴ��֪" + wa + "�ܷ��" + ac + 
                                  ma + "��������Ը"; 
        
                quest_msg = "����дһ����"; 
                type = "calligraphy"; 
                break; 
        
        case 4: 
                msg = random(2) ? "��λ" + wa + "�������ã�" + ma + "��Ϊ" 
                                  "һ�·��ǰ��������ϲ�ù��ӣ�" + ma + 
                                  "��������һ��ϲͼ�Ա�ף�أ�������" HIW 
                                  "����" NOR + WHT "����̫��������ܰ�" + 
                                  ac + "�Ҵ�������Ը��" + ma + "�м���" 
                                  "��������Ҳ�����������": 
        
                                  "�����" + ma + "�и�����֮�룬����" + wa + 
                                  "��æ" + ac + "��ɡ�" + ma + "�и�����" 
                                  "������֪��������λ" HIW "����" NOR + WHT 
                                  "���֣�����ȥ�ݷá�ȴ��֪����α�����" 
                                  "��" + wa + "�д�֮�����ܹ�Ͷ�����ã���" 
                                  "��м�����"; 
        
                quest_msg = "���һ�һ����"; 
                type = "drawing"; 
                break; 
        
        default: 
                msg = random(2) ? "�š�" + wa + "�����������" + ma + "��" 
                                  "�˶��֣���С�����˽�ǣ����ձ���ҽ�Ρ�" 
                                  "�����θ����Ҳ���һλ" HIW "ҽ��" NOR + 
                                  WHT "�õ�Ĵ�������ܰ�æ" + ac + "��" 
                                  "�ô��ˣ�" + ma + "�м�����������Ҳ����" 
                                  "�������": 
        
                                  "�����㽲��" + wa + "��ǰ����" + ma + 
                                  "���˹��У��������˵����ˣ�������δȬ��" 
                                  "�������ⲡʹ֮��ίʵ�Ѱ�����������ͨ��" 
                                  HIW "ҽ��" NOR + WHT "���ܹ�����" + ac + 
                                  ma + "��ʹ�Ļ���" + ma + "����֪����һ��" 
                                  "ȫ����֮"; 
        
                quest_msg = "����ҽ�β�ʹ"; 
                type = "medical"; 
                break; 
        } 
        
        // �ṩ�������������Ϣ 
        msg = WHT "\n" + me->name() + WHT "��˼Ƭ�̣�����" 
              "˵����" + msg + "��\n\n" NOR; 
        
        message("vision", me->name() + "��" + who->name() + 
                "����С��˵��Щʲô��\n", 
                environment(who), ({ who })); 
        
        tell_object(who, sort_msg(msg)); 
        
        // ����Ҫ������� 
        skill = type; 
        
        // Ϊʲô��ʮ����Ϊ��Ŀ�������ȼ��ļ��� 
        exp = me->query("combat_exp") * 10; 
        
        // ����������и���ܣ���ֱ�ӵ��� 
        // ���û�У���ȡ�����֧�ֵȼ������� 
        if (me->query_skill(skill)) 
                lvl = me->query_skill(skill, 1); 
        else 
                lvl = pow(exp, 1.0 / 3) - 50; 
        
        // �ȼ�̫������� 
        if (lvl < 80) lvl = 80; 
        
        // �ȼ�̫�������� 
        if (lvl > 300) lvl = 300; 
        
        /* 
        tell_object(who, HIC "��������Ϣ��" NOR + WHT + me->name() + 
                         HIW " ���飺" HIC + exp / 10 + 
                         HIW " ���" HIC + to_chinese(skill) + 
                         HIW " �ȼ���" HIC + lvl + "\n\n" NOR); 
        */ 
          
        // ע���������� 
        who->set("ultraquest/quest/type", type); 
        who->set("ultraquest/quest/name", me->query("name")); 
        who->set("ultraquest/quest/id", me->query("id"));
        who->set("ultraquest/quest/msg", quest_msg); 
        
        // ����ע�������� 
        me->set_temp("need_accede/user", who->query("id")); 
        me->set_temp("need_accede/lvl", lvl);  
        
        return; 
} 
         
// ϵͳԤ������ķ��� 
public void give_quest(object me) 
{ 
        string *lines, file; 
        string quest, next_npc, msg, npc; 
        string type, next_name, quest_msg, name, place; 
        object item, ob; 

        if (me->query("ultraquest/npc5"))  
        {
                npc = me->query("ultraquest/npc5");
                name = me->query("ultraquest/name5"); 
        } else        
        if (me->query("ultraquest/npc4"))  
        {
                npc = me->query("ultraquest/npc4");
                name = me->query("ultraquest/name4");             
        } else
        if (me->query("ultraquest/npc3"))  
        {
                npc = me->query("ultraquest/npc3"); 
                name = me->query("ultraquest/name3");
        } else
        if (me->query("ultraquest/npc2"))
        { 
                npc = me->query("ultraquest/npc2");
                name = me->query("ultraquest/name2");   
        } else
        {  
                npc = me->query("ultraquest/npc1"); 
                name = me->query("ultraquest/name1");
        }
        
        // û���ṩ�������� 
        if (! npc) return; 
                                
        switch (random(3)) 
        { 
        case 0 : 
                type = "kill";
                ob = new(CLASS_D("generate") + "/killer.c");
                NPC_D->place_npc(ob, ({ "����һ��", "����ɽ", "����", "������", "���ݳ�" }));
                NPC_D->set_from_me(ob, me, 120); 
                ob->add_temp("apply/attack", ob->query_skill("force") * 1 / 2);
                ob->add_temp("apply/dodge", ob->query_skill("force") * 1 / 2);
                ob->add_temp("apply/parry", ob->query_skill("force") * 1 / 2);
                ob->add_temp("apply/damage", 500);
                ob->add_temp("apply/unarmed_damage", 500);
                ob->add_temp("apply/armor", 500);
                ob->set_temp("quester", me->query("id"));                              
                                         
                NPC_D->random_move(ob);
                NPC_D->random_move(ob);

                next_npc = ob->query("id");
                next_name = ob->query("name"); 
                place = ob->query("place");   
                                                
                msg = random(2) ? "�����ɱ��" HIR + next_name + "(" + next_npc + ")" + NOR + 
                                  WHT "���ˣ���������ͷ�����ҡ�\n��˵�������" + place + "�����ȥ�ɣ�": 
        
                                  "��ȥ��" HIR + next_name + "(" + next_npc + ")" + NOR + WHT 
                                  "�������ˣ��������ϵ�ͷ�����ҡ�\n��˵�������" + place + "�����ȥ�ɣ�"; 
        
                quest_msg = "����ɱ��" + next_name + "(" + next_npc + ")"; 
                break; 
        /*
        case 1 : 
                type = "find";
                msg = random(2) ? "������������" + next_name + "(" + next_npc + ")" + NOR + 
                                  WHT "��ֻ���ͷ��ͷ�������": 
        
                                  "�������ܰ����ҵ�" + next_name + "(" + next_npc + ")" + NOR 
                                  + WHT "�������ҿ����ṩЩ����"; 
        
                quest_msg = "�����ҵ�" + next_name + "(" + next_npc + ")"; 
                break; 
        */
        case 1 : 
                type = "send";
                ob = new(CLASS_D("generate") + "/receiver1.c"); 
                NPC_D->place_npc(ob, ({ "����һ��", "����ɽ", "����", "������", "���ݳ�" }));
                NPC_D->set_from_me(ob, me, 100); 
        
                NPC_D->random_move(ob); 
                
                next_npc = ob->query("id");
                next_name = ob->query("name");             
                place = ob->query("place"); 
                                
                msg = random(2) ? "����Ұ�������͵�" HIY + next_name + "(" + next_npc + ")" 
                                  + NOR + WHT "���У�Ȼ����" HIW 
                                  "��ִ" NOR + WHT "�����ҡ�\n��˵�������" + place + "�����ȥ�ɣ�": 
        
                                  "���з���Ҫ�����͵�" HIY + next_name + "(" + next_npc + ")" 
                                  + NOR + WHT "��������������" 
                                  "���ɡ�\n��˵�������" + place + "�����ȥ�ɣ�"; 
        
                quest_msg = "���Ұ����͵�" + next_name + "(" + next_npc + ")" + "��"; 
                item = new("/clone/misc/letter"); 
                break; 
        
        case 2 : 
                type = "give";

                ob = new(CLASS_D("generate") + "/receiver1.c"); 
                NPC_D->place_npc(ob, ({ "����һ��", "����ɽ", "����", "������", "���ݳ�" }));
                NPC_D->set_from_me(ob, me, 100); 
        
                NPC_D->random_move(ob); 

                next_npc = ob->query("id");
                next_name = ob->query("name");             
                place = ob->query("place"); 
                                
                msg = random(2) ? "����Ұ���������͵�" HIY + 
                                  next_name + "(" + next_npc + ")" + NOR + WHT "���������" 
                                  "��ʲô��Ӧ��\n��˵�������" + place + "�����ȥ�ɣ�": 
        
                                  "�ͷ����˰���ת����" HIY + next_name + "(" + next_npc + ")"
                                  + NOR + WHT "����;��Ī˽�Դ�" 
                                  "����\n��˵�������" + place + "�����ȥ�ɣ�"; 
        
                quest_msg = "���ҰѰ���ת����" + next_name + "(" + next_npc + ")"; 
                item = new("/clone/misc/baoguo"); 
                break; 
        } 
        
        // �ṩ��������Ϣ 
        message("vision", name + "������" + me->name() + "��" 
                          "��˵��Щʲô��\n", environment(me), 
                          ({ me })); 
        
        tell_object(me, WHT + name + WHT "���Ķ���˵����" + 
                        msg + "��\n" NOR); 
        
        // ע���������� 
        me->set("ultraquest/quest/type", type); 
        me->set("ultraquest/quest/name", next_name); 
        me->set("ultraquest/quest/id", next_npc);
        me->set("ultraquest/quest/msg", quest_msg); 
        
        // �������������ߣ���ע��������� 
        if (objectp(item)) 
        { 
                item->set("send/from", name); 
                item->set("send/send", next_name); 
                item->set("send/user", me->name()); 
                item->set("long", WHT "����һ" + item->query("unit") + 
                                  name + "׼��ת����" + next_name + "��" + 
                                  item->name() + "��\n" NOR); 
        
                // �ṩ�����ת�Ƶ���Ϣ 
                message_vision(name + "�ó�һ" + item->query("unit") + 
                               item->name() + NOR "(" + item->query("id") + 
                               ")��$N" NOR "��\n" NOR, me); 
                item->move(me, 1); 
        } 
        return; 
} 
        
// ��������ķ��� 
public void quest_guard(object me, object who) 
{ 
        string msg; 
        
        message("vision", me->name() + "��" + who->name() + 
                          "����С��˵��Щʲô��\n", 
                          environment(who), ({ who })); 
        
        switch (random(3)) 
        { 
        case 0: 
                msg = "�ҵĳ�ҽ���Ҫɱ������"; 
                break; 
        
        case 1: 
                msg = "�����и��һ����Ҫ������"; 
                break; 
        
        default: 
                msg = "����˵����׼�����Ҳ���"; 
                break; 
        } 
        
        tell_object(who, WHT + me->name() + WHT "���Ķ���" 
                         "˵����" + msg + "����" HIW "����" 
                         "����" NOR + WHT "������һ�¡�\n" NOR); 
        
        // Ϊ�˷�ֹ�����ͻ��Ŀ�����ñ��������� 
        me->set_temp("start_guard", 1); 
          
        // ע�ᱣ���������� 
        who->set("ultraquest/quest/type", "guard"); 
        who->set("ultraquest/quest/name", me->query("name")); 
        who->set("ultraquest/quest/id", me->query("id"));
        who->set("ultraquest/quest/msg", "�������ﱣ����"); 
        who->start_call_out((: call_other, __FILE__, "start_guard", 
                            me, who :), 15); 
        return; 
} 
        
// ��������ķ��� 
public void quest_going(object me, object who) 
{ 
        string *lines, file; 
        string where, area, place; 
        
        // ����ϵͳԤ��ĵص����� 
        file = read_file(QUEST + "place"); 
        lines = explode(file, "\n"); 
        where = lines[random(sizeof(lines))]; 
        
        if (sscanf(where, "%s/%s", area, place) != 2) 
                return; 
        
        // ���ϵͳ���õĵ�������ʼ���ظ�����ֱ��ִ�� 
        // ϵͳԤ���������� 

        if (place == environment(me)->query("short")) 
        { 
                generate_information(who); 
                return; 
        } 

        message("vision", me->name() + "��" + who->name() + 
                          "����С��˵��Щʲô��\n", 
                          environment(who), ({ who })); 
        
        tell_object(who, WHT + me->name() + WHT "���Ķ���" 
                         "˵�����������е���Ҫ��" + HIW + 
                         area + NOR + WHT "��" HIW + place + 
                         NOR + WHT "�����ͼ������ҹ�ȥ��" 
                         "\n" NOR); 
        
        // Ŀ�꿪ʼ�����ж� 
        me->set_leader(who); 
        message_vision("$N������ʼ����$nһ���ж���\n", me, who); 
        
        // Ϊ�˷�ֹ�����ͻ��Ŀ�����ñ��������� 
        me->set_temp("start_guard", 1); 
        
        // ע�Ụ���������� 
        who->set("ultraquest/quest/type", "going"); 
        who->set("ultraquest/quest/obj", place); 
        who->set("ultraquest/quest/name", me->query("name"));
        who->set("ultraquest/quest/msg", "���ҵ�" + area + "��" + place); 
        
        // ��ʼ��ʱɨ��������ĵص� 
        who->start_call_out((: call_other, __FILE__, "check_going", 
                            me, who :), 1); 
        return; 
} 
         
// ִ�б�������ĳ��� 
void start_guard(object me, object who) 
{ 
        object killer; 
        
        if (! objectp(me) || ! objectp(who) 
            || environment(me) != environment(who)) 
                return; 
        
        if (random(5) == 1) 
        { 
                message_vision(CYN "\n$N" CYN "������ͷ����Ϊ" 
                               "���ε�˵�����ף��ѵ������д�" 
                               "\n" NOR, me); 
        
                if (random(3) == 1) 
                { 
                        message_vision(CYN "$N" CYN "��Ц����" 
                                       "������$n" CYN "������" 
                                       "����û�����ˣ���Ҳ����" 
                                       "����һ�����Ҿ͸������" 
                                       "��\n" NOR, me, who); 
        
                        // Ŀ��ȡ�������������� 
                        me->delete_temp("start_guard"); 
        
                        // ������ɣ�ע�ά������ 
                        // who->set("ultraquest/name1", me->name()); 
                        who->set("ultraquest/gift/point", 120); 
                        who->set("ultraquest/gift/msg", "��ͨ������" + 
                                 who->query("ultraquest/quest/name") + "�Ĺ���"); 
        
                        // ϵͳ����ô�����Ľ��� 
                        give_gift(who); 
                } else 
                { 
                        message_vision(CYN "$N" CYN "̾�˿���" 
                                       "����$n" CYN "��������" 
                                       "��û�����ˣ��һ�������" 
                                       "��������������ɡ�\n" 
                                       NOR, me, who); 
        
                        // Ŀ��ȡ�������������� 
                        me->delete_temp("start_guard"); 
        
                        // �����жϣ�ϵͳ���·�������� 
                        give_quest(who); 
                } 
                return; 
        } 
        message_vision(CYN "\nͻȻ��$N" CYN "��$n" CYN "����˵��" 
                       "�����ˣ�ɱ�ҵ������ˡ�\n\n" NOR, me, who); 
        
        killer = new(CLASS_D("generate") + "/killer"); 
        NPC_D->set_from_me(killer, who, 120); 
        killer->move(environment(me)); 
        
        message_vision(HIW "$n" HIW "���˹�������$N" HIW "��Ц" 
                       "����ԭ���������������ɣ�\n" NOR, me, 
                       killer); 
        
        killer->set_leader(me); 
        killer->kill_ob(me); 
        
        // ��鱣��״̬ 
        who->start_call_out((: call_other, __FILE__, "check_guard", 
                             me, who, killer :), 3); 
} 
        
// ��鱻���������״̬ 
void check_guard(object me, object who, object killer) 
{ 
        if (! objectp(me) && ! objectp(killer)) 
                return; 
        
        // ����ս�������ӳټ�� 
        if (objectp(killer) && objectp(me) 
            && (me->is_fighting(killer) 
            || who->is_fighting(killer))) 
        { 
                who->start_call_out((: call_other, __FILE__, "check_guard", 
                                    me, who, killer :), 1); 
                return; 
        } 
        
        // ������������ʧ�������ж� 
        if (! objectp(me) 
            && objectp(killer)) 
        { 
                tell_object(who, HIG "���ۼ�" + who->query("ultraquest/quest/name") + 
                                 HIG "��ɱ�������������㡣\n" NOR); 
        
                // ��¼��ʧ�ܼ�¼ 
                who->set("ultraquest/fail", 1); 
                return; 
        } 
        
        // ɱ����ʧ�ұ������˴��ڣ�������� 
        if (! objectp(killer) 
            && objectp(me)) 
        { 
                // ����������˻��ԣ�����ת�� 
                if (! living(me)) 
                        me->revive(); 
        
                message_vision(CYN "$N" CYN "���˲�������$n" CYN "��������" 
                               "���������æ���м�������\n$N" CYN "���ŵ���" 
                               "����֮�����Իر�����һ������֪���Ķ�������" 
                               "��\n" NOR, me, who); 
        
                // Ŀ��ȡ�������������� 
                me->delete_temp("start_guard"); 
        
                // ������ɣ�ע�ά������ 
                // who->set("ultraquest/name1", me->name()); 
                who->set("ultraquest/gift/point", 250); 
                who->set("ultraquest/gift/msg", "��ͨ������" + 
                who->query("ultraquest/quest/name") + "�Ĺ���"); 
        
                // ϵͳ����ô�����Ľ��� 
                give_gift(who); 
                return; 
        } 
        message_vision(CYN "$N" CYN "���˿����ܣ���е�����" 
                       "ʦ��BUG��BUG��\n" NOR, who); 
        return; 
} 
          
// ��黤�������״̬ 
void check_going(object me, object who) 
{ 
        string msg, place; 
        
        // �������Ѿ�ʧ�ܣ���ȡ�������Բ����ж����� 
        if (who->query("ultraquest/fail")) 
        { 
                who->delete_temp("dest_npc"); 
                return; 
        } 
        
        // ��������»��͵���������ˣ�ִ�����³��� 
        if (! objectp(me) || ! objectp(who)) return;

        // ���ó����͵�Ŀ�ĵ� 
        place = who->query("ultraquest/quest/obj"); 
                
        if (environment(me) != environment(who)) 
        { 
                switch (who->query_temp("dest_npc")) 
                { 
                case 0: 
                        msg = "���ͷ�����䣬ȴ������" + me->name() 
                              + "����֪��ʱ��������Ӱ��\n�����а���" 
                              "����ǧ����������ϵ��ˣ��øϽ�������" 
                              "������"; 
                        break; 
        
                case 1: 
                        msg = "��������Ϊ�������ף�" + me->name()
                              + "�Ǽһﵽ������ȥ�ˡ�"; 
                        break; 
        
                case 2: 
                        msg = "���ĵ�ֱ�ʲôʱ���ˣ��Ǹ�����" + 
                              me->name() + "��ô������������"; 
                        break; 
        
                default: 
                        msg = "����������̾Ϣ���������׻��ǰ��˸�" 
                              "�����ˡ�������������"; 
        
                        // ��¼��ʧ�ܼ�¼ 
                        who->set("ultraquest/fail", 1); 
                        break; 
                } 
        
                // �������ﶪʧ��ʱ��Σ��������������ж� 
                who->add_temp("dest_npc", 1); 
        
                // ��һ��ʱ�����������ɨ�� 
                who->start_call_out((: call_other, __FILE__, "check_going", 
                                    me, who :), 5); 
        
                tell_object(who, HIG "\n" + msg + "\n\n" NOR); 
                return; 
        } 
        
        // ����Ⱥ��������ʱ��� 
        if (who->query_temp("dest_npc")) 
                who->delete_temp("dest_npc");        
        
                                       
        // �鿴��ǰλ�ã���ΪĿ�ĵأ���������� 
        if (environment(me)->query("short") == (string)who->query("ultraquest/quest/obj")) 
        { 
                // ����������˻��ԣ�����ת�� 
                if (! living(me)) 
                        me->revive(); 
        
                message_vision(CYN "$N" CYN "���˲�������$n" CYN "����лл" 
                               "�㽫���͵�" + place + "��·�������鷳���ˡ�" 
                               "\n$N" CYN "���ŵ����������ⷬ����ķ��ϣ���" 
                               "�͸�����һЩ�����ɡ�\n" NOR, me, who); 
        
                // Ŀ��ȡ�������������� 
                me->delete_temp("start_guard"); 
        
                // Ŀ�겻�ٸ��� 
                me->set_leader(0); 
        
                // ������ɣ�ע�ά������ 
                // who->set("ultraquest/name1", me->name()); 
                who->set("ultraquest/gift/point", 220); 
                who->set("ultraquest/gift/msg", "��ͨ������" + 
                                                 who->query("ultraquest/quest/name") + "�ִ�" + 
                                                 place + "�Ĺ���"); 
        
                // ϵͳ����ô�����Ľ��� 
                give_gift(who); 
                return; 
        } else 
        { 
                string last_place; 
        
                // ����¼�ʹ����ϵ͵Ļ���Ŀ��ͣ�� 
                if (stringp(last_place = me->query_temp("last_place")) 
                    && last_place != environment(me)->query("short") 
                    && ! me->is_busy() 
                    && me->query("combat_exp") < 2000000 
                    && random(50) == 1) 
                { 
                        switch (random(5)) 
                        { 
                        case 0: 
                                msg = "ͻȻ��$N" HIW "�ܵü��ˣ�һ���" 
                                      "�Ե�·�ߣ�����ѽѽ�и���ͣ��"; 
                                break; 
        
                        case 1: 
                                msg = "ֻ��$N" HIW "��Ϣ����" + who->name() 
                                      + HIW "�������㡭�������������ˡ�"; 
                                break; 
        
                        case 2: 
                                msg = "$N" HIW "���ס���һ�����ƺ�������" 
                                      "ʲô��������Ų���ʱ����������"; 
                                break; 
        
                        case 3: 
                                msg = "$N" HIW "��Ȼ��ɫ�Ұף�����" + 
                                      who->name() + HIW "���ͷ�ͣ��ͣһ" 
                                      "�ᣬ���߲����ˡ�"; 
                                break; 
        
                        default: 
                                msg = "ȴ��$N" HIW "������䣬�ߵ���·��" 
                                      "͹���һ���ʯ��ֱʹ�ù�����ȥ��"; 
                                break; 
                        } 
                        message_vision(HIW "\n" + msg + "\n\n" NOR, me, who); 
                        me->start_busy(2 + random(2)); 
                } 
        
                // �趨��һ��������ĵص㣬����뵱ǰ�ص㲻ͬ���� 
                // ִ����������ͣ���ĳ��� 
                me->set_temp("last_place", environment(me)->query("short")); 
        
                // δ����Ŀ�ĵأ���ʱ������ɨ�� 
                who->start_call_out((: call_other, __FILE__, "check_going", 
                                    me, who :), 1); 
                return; 
        } 
        return; 
} 
          
// ���������������ļ������������� 
int need_accede(object me, object who) 
{ 
        string skill, ma, wa; 
        string suc_msg, fai_msg, msg; 
        int lvl; 
        
        // ׼���Ƚϵļ������� 
        skill = who->query("ultraquest/quest/type"); 
        lvl = me->query_temp("need_accede/lvl", lvl); 
           
        // ���˳����򵥻� 
        ma = RANK_D->query_self(me); 
        wa = RANK_D->query_respect(who); 
        
        switch (skill) 
        { 
        case "mathematics" : 
                suc_msg = me->name() + "���˵�ͷ���漴�����������ڵ��滭" 
                          "��Щ��ֱ������ԲȦ������д�¡�̫����Ԫ����Ԫ��" 
                          "��Ԫ����Ԫ�����֡�����һ��ĬĬϸ�ۣ���ָ�����" 
                          "����������Ĵ��������ڸ�֮" + me->name() + 
                          "��" + me->name() + "����һ����̾������ԭ��Ϊ��" 
                          "�������ˣ����ˡ�"; 
        
                fai_msg = me->name() + "���˵�ͷ���漴�����������ڵ��滭" 
                          "��Щ��ֱ������ԲȦ������д�¡�̫����Ԫ����Ԫ��" 
                          "��Ԫ����Ԫ�����֡�����һ�Կ��ò�֪���ƣ�ȫȻ��" 
                          "֪��������֡�" + me->name() + "���˰��죬����" 
                          "���޶��������ɵ������һЦ��"; 
                break; 
        
        case "literate" : 
                suc_msg = me->name() + "���˵�ͷ��������ɤ�ӵ����ҳ�һ��" 
                          "����������ҶԳ��������������ǡ��л�Ӣ��ʷ����" 
                          "��΢΢һЦ����ڶԵ���������ɵ��Ĺ����" + 
                          me->name() + "����һ���޵���������˾��"; 
        
                fai_msg = me->name() + "���˵�ͷ��������ɤ�ӵ����ҳ�һ��" 
                          "����������ҶԳ����������������ǡ��л�Ӣ��ʷ��" 
                          "��������һ㶣������˰���ŵ��������������ƻ���" 
                          "����" + me->name() + "�����ŭ����������ޣ���" 
                          "��ʲô���ӡ����֪���ƶԺ�ô��"; 
                break; 
        
        case "chess" : 
                suc_msg = "�㵱������ǰȥ����" + me->name() + "�ڿ����" 
                          "����������������ʱ��ȴ��" + me->name() + "��" 
                          "�Ǵ����졣��������������һ�ӣ�" + me->name() + 
                          "��ʱ��ɫ���࣬��Ȼ���������ˣ������ˡ�������" 
                          "���ǡ�"; 
        
                fai_msg = "�㵱������ǰȥ����" + me->name() + "�ڿ����" 
                          "����������������ʱ�����ѱ�" + me->name() + 
                          "�Ƶýڽڰ��ˣ����������" + me->name() + "��" 
                          "����ɫ���࣬��Ц������ô��������ˮƽ��������" 
                          "��ô��"; 
                break; 
        
        case "calligraphy" : 
                suc_msg = "��΢΢һЦ����������ǰȥ���ӹ�ë�ʱ㿪ʼ��д" 
                          "��������ʱֻ��������������б�ī��������" 
                          "�����������ּ�����������ˮ�����潫�鷨���⾳" 
                          "���ӵ����쾡�¡�" + me->name() + "��һ�Կ���" 
                          "Ŀ�ɿڴ����������ޡ�"; 
        
                fai_msg = "�㵱������ǰȥ���ӹ�ë�ʱ�մīˮ���㿪ʼ��д" 
                          "������������д�������緢֮����̧ͷ��ȴ����" + 
                           me->name() + "��ɫ��Ϊ�ѿ������ɵ�΢΢һ㶡�" + 
                           me->name() + "ҡ��ҡͷ��ʧ�����������ҽ�������" 
                           "���ó��֣�������˳�Ц��ԭ����������"; 
                break; 
        
        case "drawing" : 
                suc_msg = "��΢΢һЦ�������ӹ����ʣ����������ī������" 
                          "��ī�����죬�����۽�����ֻ�������ʣ����ƿ���" 
                          "ʵ������" + me->name() + "��һ��Խ��Խ����ϲ" 
                          "���������ޡ�"; 
        
                fai_msg = "�㵱������ǰȥ���ӹ������������������㻭��" 
                          "�����緢֮ʱ��̧ͷ��ȴ����" + me->name() + "��" 
                          "ɫ��Ϊ�ѿ������ɵ�΢΢һ㶡�" + me->name() + 
                          "ҡ��ҡͷ��ʧ���������ˣ����ˡ�������ˮƽ����" 
                          "û���Լ����ֻ��׵���"; 
                break; 
        
        default: 
                suc_msg = "����˵�ͷ�������ָ����" + me->name() + "��" 
                          "���ϣ�����Ƭ�̱��ѷ����䲡�����ڡ�����Ҳ����" 
                          "�飬���������ҩ����" + me->name() + "�����" 
                          "ϲ�������ҽ���������" + wa + "���˷���������" 
                          "���Իر���"; 
        
                fai_msg = "�����㶣�����ǰȥ��" + me->name() + "������" 
                          "̽�˰��죬ȴ����" + me->name() + "�����쳣��" 
                          "�ң�Զ���Լ���ʶ��" + me->name() + "�����ü" 
                          "��չ�����ɵó�̾�������������˱���һ��ӹҽ��" 
                          "�Σ�Ҳ����Ϊ���ˡ�"; 
                break; 
        } 
        
        message("vision", "ֻ��" + who->name() + "����ǰȥ����" + 
                          me->name() + "�����ֹ��˼��䡣\n", 
                          environment(who), ({ who })); 
        
        if (who->query_skill(skill, 1) >= lvl) 
        { 
                // �ύ�ɹ���������Ϣ 
                tell_object(who, sort_msg(WHT + suc_msg + "\n\n" NOR)); 
        
                // ������ɣ�ע�ά������ 
                // who->set("ultraquest/name1", me->name()); 
                who->set("ultraquest/gift/point", 350); 
                who->set("ultraquest/gift/msg", "��ͨ���˷�����" + 
                                                 me->name() + "�ľ���"); 
        
                if (! who->is_busy()) 
                        who->start_busy(3); 
        
                // ������轱����Ʒ 
                if (random(5) == 1) 
                { 
                        message_vision(CYN "$N" CYN "����" + wa + "��Ϊ��" 
                                       "ʵ��" + ma + "�۷����ѡ�һ�㱡��" 
                                       "���ɾ��⡣\n" NOR, me); 
        
                        who->set("ultraquest/gift/item", 1); 
                } 
        
                // ϵͳ����ô�����Ľ��� 
                give_gift(who); 
        } else 
        { 
                // �ύʧ�ܵ�������Ϣ 
                tell_object(who, sort_msg(WHT + fai_msg + "\n\n" NOR)); 
        
                message_vision(CYN "$N" CYN "ҡ��ҡͷ����$n" 
                               CYN "����Ҳ�գ��һ������½���" 
                               "�������������ɡ�\n" NOR, me, who); 
        
                // �����жϣ�ϵͳ���·�������� 
                give_quest(who); 
        } 
        // ע�������������������� 
        me->delete_temp("need_accede"); 
        
        return 1; 
}
          
// ���������������Ʒ 
int accept_object(object me, object who, object ob) 
{ 
        string msg; 
        string type, npc; 
        int ultra_count;
        int exp;                // ��õľ���
        int pot;                // ��õ�Ǳ��
        int mar;                // ��õ�ʵս���
        int weiwang;            // ��õ�����
        int score;              // ��õĽ�������
        int lvl;                // ����ĵȼ�
        mixed special = 0;      // �Ƿ������⽱��
        object ob1, rob;
        
        // ���û����ȡ���� 
        if (! mapp(who->query("ultraquest"))) 
                return 0; 
     
        if (me->query("name") == QUESTER)
        {                        
                switch (who->query("ultraquest/type"))
                {
                case "find":
                        if (ob->query("id") != who->query("ultraquest/id"))
                                return 0;
                                
                        message_vision(CYN "$N" CYN "���˿�" + ob->name() 
                                       + NOR + CYN "��΢΢�ĵ��˵�ͷ��\n" NOR, me); 
                        // destruct(ob); 
                        break;
                        
                case "give":
                case "rescue":
                        if (! ob->is_receipt())
                                return 0;
                        
                        if (ob->query("reply_to") != me->query("name")
                        ||  ob->query("reply_by") != who->query("ultraquest/id")
                        ||  ob->query("receive_from_name") != who->name(1))
                        {
                                message_vision("$N��ü���������������ո�ʲô����\n", me);
                                return 0;
                        }
                        
                        message_vision(CYN "$N" CYN "�ӹ�" + ob->name() + NOR + CYN
                                       "����ϸ���˿��������˵���ܺá�\n" NOR, me); 
                        // destruct(ob);
                        break;
                        
                case "kill":
                        if(! ob->is_corpse() && ! ob->is_head())
                                return 0;
                                
                        if (! stringp(ob->query("owner_id"))) 
                        { 
                                message_vision(CYN "$N" CYN "���ű��ӿ��˿�" + ob->name() 
                                               + NOR + CYN "������ʲô�����ģ������" 
                                               "���ߡ�\n" NOR, me); 
                                return 0; 
                        }

                        if (ob->query("killed_by") != who->query("id"))
                                return 0;
                                      
                        if (ob->query("victim_name") != who->query("ultraquest/name"))
                                return 0;
                                
                        // message_vision(CYN "$N" CYN "���˿�" + ob->name() 
                        //                + NOR + CYN "��΢΢�ĵ��˵�ͷ��\n" NOR, me); 
                        // destruct(ob); 
                        break;
                }
                
                msg = CYN "$N" CYN "�ӹ�" + ob->name() + NOR + CYN"����ϸ����" 
                      "���������˵���ܺá�\n" NOR; 
                      
                // ����Ҫ�������������
                who->add("ultra_count", 1);                 
                
                ultra_count = who->query("ultra_count");

                lvl = NPC_D->check_level(who); 
                exp = 18000 + random(5000) + lvl * 10; 
                pot = 18000 + random(3000) + lvl * 10; 
                mar = 1000 + random(1000); 
                weiwang = 200 + random(300) + lvl * 10; 
                score = 200 + random(300) + lvl * 10; 
                
                // ����������ɵĴ�����������
                if (ultra_count >= 100)
                {
                        // ��������˳���100�ε�����
                        exp += 800 + random(ultra_count + 1);
                        pot += 450 + random(ultra_count + 1);
                        mar += 500 + random(200);
                        weiwang += 80 + random(200);
                        score += 40 + random(150);
                } else 
                if (ultra_count >= 50) 
                { 
                        // ��������˳���50�ε����� 
                        exp += 700 + random(ultra_count + 1); 
                        pot += 400 + random(ultra_count + 1); 
                        mar += 200 + random(100); 
                        weiwang += 50 + random(150); 
                        score += 30 + random(100); 
                } else 
                if (ultra_count >= 25)
                {
                        // ��������˳���25�ε�����
                        exp += 500 + random(ultra_count + 1);
                        pot += 300 + random(ultra_count + 1);
                        mar += 100 + random(50); 
                        weiwang += 30 + random(100);
                        score += 20 + random(100);
                } else
                if (ultra_count >= 10)
                {
                        // ��������˳���10�ε�����
                        exp += 450 + random(ultra_count + 1);
                        pot += 250 + random(ultra_count + 1);
                        weiwang += 10 + random(50);
                        score += 10 + random(50);
                }
                
                if (ultra_count == 10)
                {
                        msg += CYN "$N" CYN "������Ц����������������ģ�������ʮ"
                               "��������ɵ�ƯƯ�������ܺã��ܺá���\n" NOR;
			special = 1;
                } else
                if (ultra_count == 25)
                {
                        msg += CYN "$N" CYN "��ϲ��������������ʵ������ʮ��"
                               "������ɵúܺá���\n NOR";
                        special = "/clone/fam/max/naobaijin";
                } else
                if (ultra_count == 50)
                {
                        msg += CYN "$N" CYN "̾���������ǳ���������ǰ�ˣ��벻���������ʮ"
                               "��������һ��©�����ף����ף���\n" NOR;
                        special = "/clone/fam/max/longjia";
                } else
                if (ultra_count >= 100)
                {
                        msg += CYN "$N" CYN "����̾�˿������������벻���������ϰٴ�"
                               "������һʧ�֣�����������̶���Ǻ�����˰�����\n" NOR;
                        special = "/clone/fam/max/zhenyu";
                        ultra_count = 0;
                } else
                if ((ultra_count % 10) == 0)
                {
                        msg += CYN "$N" CYN "ϲ���������ǲ�������Ȼ����" +
                               chinese_number(ultra_count) +
                               "�ζ�û��ʧ�֣��ɵĺã���\n" NOR ;
                }
                
                if (stringp(special))
                {
                        ob1 = new(special);
                        ob1->move(who, 1);
                        tell_object(who, HIM "������һ" + ob1->query("unit") + ob1->name() +
                                         HIM "��\n" NOR);
                }
                                              
                message_vision(msg, me, who); 
                if ((ultra_count >= 10 && random(200) == 1) || special) 
                        special_bonus(who); 
                        
                who->set("ultra_count", ultra_count);
                who->delete("ultraquest");

                GIFT_D->delay_work_bonus(who, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                                 "weiwang" : weiwang, "score" : score ]), 1);                
                destruct(ob); 
                return 1;
        }
                                
        // ֻ��ɱ�ˡ�Ѱ�����/�����������ִ����Ʒ���� 
        if (! stringp(type = who->query("ultraquest/quest/type")) 
            || (type != "kill" && type != "find" 
            && type != "give" && type != "send")) 
                return 0; 
        
        // �������Ϊ�����ż��������NPC 
        if (me->query("id") == who->query("ultraquest/quest/id")) 
        { 
                switch (type) 
                { 
                case "send" : 
                        if (! ob->is_letter()) 
                                return 0; 
        
                        if (ob->query("send/send") != me->name()) 
                        { 
                                message_vision(CYN "$N" CYN "��ü�����������ô����" 
                                               "�����ֲ���д���ҵġ�\n" NOR, me); 
                                return 0; 
                        } 
        
                        if (ob->query("send/user") != who->name()) 
                        { 
                                message_vision(CYN "$N" CYN "��ü����������˭������" 
                                               "�ģ�����ô����ʶ��\n" NOR, me); 
                                return 0; 
                        } 
        
                        message_vision(CYN "$N" CYN "���˿�" + ob->name() 
                                       + NOR + CYN "�����ÿɷ�ĵ��˵�ͷ��\n" NOR, me); 
                         
                        rob = new("/clone/misc/receipt"); 
                        rob->set("reply_by", me->query("name")); 
                        rob->set("reply_to", ob->query("send/from")); 
                        rob->set("receive_from", who->query("id"));
                        rob->set("long", "����һ����" + me->name() + "�յ�������д�Ļ�ִ��\n"); 
                        rob->move(who, 1); 
                        message_vision("$N����$nһ�Ż�ִ��\n", me, who);                 
                        destruct(ob);
                        
                        break; 
        
                case "give" : 
                        if (! ob->is_bag()) 
                                return 0; 
        
                        if (ob->query("send/send") != me->name()) 
                        { 
                                message_vision(CYN "$N" CYN "��ü�����������ô����" 
                                               "�����ֲ����ø��ҵġ�\n" NOR, me); 
                                return 0; 
                        } 
        
                        if (ob->query("send/user") != who->name()) 
                        { 
                                message_vision(CYN "$N" CYN "��ü�����������˭����" 
                                               "�ģ��������Լ����Űɡ�\n" NOR, me); 
                                return 0; 
                        } 
        
                        message_vision(CYN "$N" CYN "���˿�" + ob->name() 
                                       + NOR + CYN "�����ÿɷ�ĵ��˵�ͷ��\n" NOR, me); 
                        rob = new("/clone/misc/receipt"); 
                        rob->set("reply_by", me->query("name")); 
                        rob->set("reply_to", ob->query("send/from")); 
                        rob->set("receive_from", who->query("id"));
                        rob->set("long", "����һ����" + me->name() + "�յ��İ���д�Ļ�ִ��\n"); 
                        rob->move(who, 1); 
                        message_vision("$N����$nһ�Ż�ִ��\n", me, who);          
                        destruct(ob); 
                        break; 
                } 
                
                who->set("ultraquest/gift/point", 200); 
                who->set("ultraquest/gift/msg", "��ͨ���˷�����" + 
                                                 me->name() + "�ľ���"); 
                // give_gift(who);
                return 1; 
        } 
        
        // �������Ϊ���������NPC 
        if (who->query("ultraquest/npc5"))  
        {
                npc = who->query("ultraquest/npc5");        
        } else
        if (who->query("ultraquest/npc4"))  
        {
                npc = who->query("ultraquest/npc4");        
        } else
        if (who->query("ultraquest/npc3"))  
        {
                npc = who->query("ultraquest/npc3"); 
        } else
        if (who->query("ultraquest/npc2"))
        { 
                npc = who->query("ultraquest/npc2");    
        } 
        
        if (me->query("id") == npc) 
        { 
                switch (type) 
                { 
                case "kill":
                        if(! ob->is_corpse() && ! ob->is_head())
                                return 0;
                                
                        if (! stringp(ob->query("owner_id"))) 
                        { 
                                message_vision(CYN "$N" CYN "���ű��ӿ��˿�" + ob->name() 
                                               + NOR + CYN "������ʲô�����ģ������" 
                                               "���ߡ�\n" NOR, me); 
                                return 0; 
                        }
        
                        if (ob->query("killed_by") != who->query("id"))
                                return 0;   
                                             
                        if (ob->query("victim_name") != who->query("ultraquest/quest/name"))
                                return 0;
                                
                        message_vision(CYN "$N" CYN "���˿�" + ob->name() 
                                       + NOR + CYN "�����ÿɷ�ĵ��˵�ͷ��\n" NOR, me); 
                        // destruct(ob); 
                        break;  
                                              
                case "find" : 
                        if (ob->query("id") != who->query("ultraquest/quest/id"))
                                return 0;
                                
                        message_vision(CYN "$N" CYN "���˿�" + ob->name() 
                                       + NOR + CYN "�����ÿɷ�ĵ��˵�ͷ��\n" NOR, me); 
                        // destruct(ob); 
                        break; 
                        
                case "send" :
                        if (! ob->is_receipt())  return 0;
                        message_vision(CYN "$N" CYN "���˿�" + ob->name()
                                       + NOR + CYN "�����ÿɷ�ĵ��˵�ͷ��\n" NOR, me);

                        if (ob->is_receipt()) 
                        { 
                                if (ob->query("reply_to") != me->query("name"))
                                {
                                        message_vision("$N��ü���������������ո�ʲô����\n", me);
                                        return 0;
                                }
                                
                                if (ob->query("receive_from") != who->query("id") ||
                                    ob->query("reply_by") != who->query("ultraquest/quest/name"))
                                {
                                        message_vision("$N��ü����������������͵��𣿡�\n", me);
                                        return 0;
                                }
                                // destruct(ob);
                        }
                           
                        break;

                case "give" :
                        if (! ob->is_receipt())  return 0;
                        message_vision(CYN "$N" CYN "���˿�" + ob->name()
                                       + NOR + CYN "�����ÿɷ�ĵ��˵�ͷ��\n" NOR, me);
                        if (ob->is_receipt()) 
                        { 
                                if (ob->query("reply_to") != me->query("name"))
                                {
                                        message_vision("$N��ü���������������ո�ʲô����\n", me);
                                        return 0;
                                }
                                
                                if (ob->query("receive_from") != who->query("id") ||
                                    ob->query("reply_by") != who->query("ultraquest/quest/name"))
                                {
                                        message_vision("$N��ü����������������͵��𣿡�\n", me);
                                        return 0;
                                }
                                // destruct(ob);
                        }
                        break;                        
                } 
                
                destruct(ob);
                who->set("ultraquest/gift/point", 600); 
                who->set("ultraquest/gift/msg", "��ͨ���˷�����" + 
                                                 me->name() + "�ľ���"); 
                give_gift(who);
                
                return 1; 
        } 
} 
        
// �������Ľ��� 
public void give_gift(object me) 
{ 
        int gift; 
        
        // ���û��ע�ά�����������ж� 
        if (! me->query("ultraquest/gift/msg") 
                || ! me->query("ultraquest/gift/point")) 
                return; 
        
        // ����������ɵ����� 
        me->add("ultraquest/finish", 1); 
         
        // ������Ʒ���� 
        if (me->query("ultraquest/gift/item")) 
                special_bonus(me); 
         
        // �����ĵ��� 
        gift = me->query("ultraquest/gift/point") + 
                me->query("ultraquest/finish"); 
        
        GIFT_D->delay_work_bonus(me, ([ "prompt"  : me->query("ultraquest/gift/msg"), 
                                        "exp"     : random(gift) + gift, 
                                        "pot"     : random(gift / 2) + gift / 2, 
                                        "score"   : random(gift / 20) + gift / 20, 
                                        "weiwang" : random(gift / 30) + gift / 30, ])); 
        
        // ȡ����ԭ������������ 
        me->delete("ultraquest/gift"); 
        me->delete("ultraquest/quest"); 
        
        // �ṩ�µ��������Ա��������� 
        generate_information(me); 
        return; 
} 
          
// �������ṩ��������Ϣ 
public void generate_information(object me) 
{
        object ob; 
        string *lines, file; 
        string where, next_npc, next_name, npc_place, place; 
        string npc, npc1, npc2, npc3, npc4, msg, ma; 
        string name;
        int finish;

        // ������ĸ����������뱾������Ķ���
        if (me->query("ultraquest/npc5"))
        {              
                switch(me->query("ultraquest/type"))
                {
                case "kill":
                        ob = new(CLASS_D("generate") + "/killer1.c");
                        NPC_D->place_npc(ob, ({ "����һ��", "����ɽ", "����", "������", "���ݳ�", "����" }));
                        NPC_D->set_from_me(ob, me, 150); 
                        ob->add_temp("apply/attack", ob->query_skill("force") * 1 / 2);
                        ob->add_temp("apply/dodge", ob->query_skill("force") * 1 / 2);
                        ob->add_temp("apply/parry", ob->query_skill("force") * 1 / 2);
                        ob->add_temp("apply/damage", 1000);
                        ob->add_temp("apply/unarmed_damage", 1000);
                        ob->add_temp("apply/armor", 1000);
                        ob->set_temp("quester", me->query("id"));      
                        
                        me->set("ultraquest/id", ob->query("id"));
                        me->set("ultraquest/name", ob->query("name")); 
                                         
                        NPC_D->random_move(ob);
                        NPC_D->random_move(ob);
                        NPC_D->random_move(ob);
                        
                        place = ob->query("place");
                        
                        tell_object(me, CYN + me->query("ultraquest/name5") + CYN "С������˵����" 
                                        NOR + HIR + ob->name() + "(" + ob->query("id") + ")" + NOR + CYN
                                        "����Ļ�����ˣ���ǧ��Ҫ˵����˵��\n��˵�������" + place + "�����ȥ�ɣ�\n" NOR);                         
                        break;
                case "send":
                        break;
                case "rescue":
                        break;
                case "find":
                        break;
                }
                return;
        }  
                      
        // �����Ǹ�����һ�������Ķ���
       if (me->query("ultraquest/npc4"))  
        {
                npc4 = me->query("ultraquest/npc4");
                name = me->query("ultraquest/name4");
                npc = npc4;             
        } else
        if (me->query("ultraquest/npc3"))  
        {
                npc3 = me->query("ultraquest/npc3"); 
                name = me->query("ultraquest/name3");
                npc = npc3;
        } else
        if (me->query("ultraquest/npc2"))
        { 
                npc2 = me->query("ultraquest/npc2");
                name = me->query("ultraquest/name2");
                npc = npc2;       
        } else
        {  
                npc1 = me->query("ultraquest/npc1"); 
                name = me->query("ultraquest/name1");
                npc = npc1;
        }
                                
        // û����һ���ṩ�������� 
        if (! npc) return; 

        ob = new(CLASS_D("generate") + "/cluenpc.c");
        NPC_D->place_npc(ob, ({ "����һ��", "����ɽ", "����", "������", "���ݳ�" }));
        NPC_D->set_from_me(ob, me, 100); 
        ob->add_temp("apply/attack", ob->query_skill("force") * 1 / 2);
        ob->add_temp("apply/dodge", ob->query_skill("force") * 1 / 2);
        ob->add_temp("apply/parry", ob->query_skill("force") * 1 / 2);
        ob->add_temp("apply/damage", 500);
        ob->add_temp("apply/unarmed_damage", 500);
        ob->add_temp("apply/armor", 500);
        ob->set_temp("quester", me->query("id"));                              
                                                 
        NPC_D->random_move(ob);

        next_npc = ob->query("id");
        next_name = ob->query("name"); 
        npc_place = ob->query("place");   
                        
        // ��¼����һ���������Ｐ���ֵ� 
        if (npc4) 
        {
                me->set("ultraquest/npc5", next_npc); 
                me->set("ultraquest/name5", next_name); 
        }
        else
        if (npc3)
        { 
                me->set("ultraquest/npc4", next_npc);
                me->set("ultraquest/name4", next_name);
        }
        else
        if (npc2) 
        {
                me->set("ultraquest/npc3", next_npc);
                me->set("ultraquest/name3", next_name);
        }
        else
        if (npc1) 
        {
                me->set("ultraquest/npc2", next_npc);
                me->set("ultraquest/name2", next_name);
        }
        
        me->set("ultraquest/place", npc_place); 
        
        // ����ϴε�������Ϣ
        me->delete("ultraquest/quest");
        
        // �����Ŀ����ɫ 
        next_name = HIY + next_name + "(" + next_npc + ")" + NOR + WHT; 

        // ���˳����򵥻� 
        ma = RANK_D->query_respect(me); 
        
        // ���������������
        finish = me->query("ultraquest/finish");
        switch (finish)
        {
        case 1:
                msg = "��˵�����Ļ���������ʧ��һ����Ҫ��Ʒ��ͨ�������Ʒ����֪"
                      "������˭��\n����" + npc_place + "��" + next_name + "��֪����"
                      "����Ʒ�����䡣\n" + ma + "��ȥ�������ʣ���Ҳ��֪�����Ǽ�";
                break;

        case 2:
                msg = "����Ʒ�ҵ�����˵��������" + ma + "֪��" + npc_place + "��\n"
                      "�����и�" + next_name + "��������Ҫ�ҵ��Ƕ�������������";
                break;

        case 3:
                msg = "��֪" + ma + "��ʶ" + npc_place + "��" + next_name + "��\n"
                      "�������治�ɣ��Ǹ��������ϸ����͸����ˣ��������������";
                break;

        case 4:
                msg = "���ź�����Ҫ�Ķ�����ǰ����㶪�ˣ������" + ma + "�Ƿ���ʶ" 
                      + npc_place + "��" + next_name + "��\n�������˶��������Һ���֪"
                      "���Ǹ���Ʒ��������˭";
                break;

        default:
                msg = "�����롭" + ma + "ȥ��" + npc_place +
                      "��" + next_name + "���ʿ��ɡ�\nȥ������"
                      "��˵��������";
                break;
        }
        
        // ��ʼ����������������ˢ������ 
        if (name == QUESTER) 
        { 
                if (me->query("ultraquest/begin")) 
                        msg = "���š���ȥ" + npc_place + 
                              "����" + next_name + "�������Ƕ�" 
                              "�ƺ�����Щ����"; 
                else 
                        msg = "�����ȥ" + npc_place + 
                              "��" + next_name + "������������" 
                              "���ƺ���Щ����"; 
        } 

        // �͵�ı���ֻҪ��Ǯ�ͺ�˵�� 
        if (name == LURCHER) 
        { 
                switch (random(3)) 
                { 
                case 0: 
                        msg = "���ٺ١���ȥ" + npc_place + 
                              "��䣬�Ƕ��и�" + next_name + 
                              "��������ɶ��֪��"; 
                        break; 

                case 1: 
                        msg = "�������ɡ���ȥ��" + next_name + 
                              "���ʿ����Ǽһ����" + npc_place + 
                              "���ɱ��߶���"; 
                        break; 

                default: 
                        msg = "�㵽" + npc_place + "�����" 
                              "������" + next_name + "���ˣ�˵" 
                              "�������ٺ١�����ɶ�ջ�"; 
                        break; 
                } 
        } 

        // �ṩ��������Ϣ 
        message("vision", name + "������" + me->name() + "��" 
                "��˵��Щʲô��\n", environment(me), 
                ({ me })); 
 
        // �ṩ�������������Ϣ 
        msg = WHT + name + WHT "���Ķ���˵����" + msg + "��\n" NOR; 

        // tell_object(me, sort_msg(msg)); 
        tell_object(me, msg);

        return; 
} 

