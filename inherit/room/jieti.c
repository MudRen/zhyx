#include <ansi.h>

string *jieti_msg = ({
        HIM "����ϥ���ڵ��ϣ�ƽ�ľ��������Ž���Ϣ������ѭ��ʮ�����죬����\n" NOR
        HIM "��ȫ��ͨ���裬�����������ķ�\n\n" NOR            
        HIR "            ��     ħ       ��      ��     ��     ��\n\n" NOR,
        
        HIW "��ʱֻ����һ������׹���������������ܲ���������ɫ���绮��\n" NOR 
        HIW "���գ���˿�����з��ģ�������ħ��������������������ֳ�����\n" NOR 
        HIW "�֣��ֱ���뵤����ٻ��У�ֻ�о�����Ͱٻ������˵̵�ˮ��һ\n" NOR 
        HIW "�㣬�����������ˮ�Ƶ���ǰ��ȥ���������������ľ���˲�䱻�ݻ١�\n" NOR,
        HIC "����˲�䱻�ٵľ�ʹ��Щʹ����ȥ�����崫��˺���ѷε�ʹ�࣬��\n" NOR 
        HIC "�����������ȫŤ���ˡ��������ʱ�䶼������������о����񾭹�\n" NOR 
        HIC "����������᳤һ�㡣\n" NOR ,
        HIM "��Ѩ��������������Ἧ������Ѩ�����ĵط����������������ںϣ�\n" NOR 
        HIM "�����γ�̫����״������������������������������������̫�����ᣬ\n" NOR 
        HIM "����̫��ͼ��ͻȻһ�����������Ҳ�����͵�����һ�£���֪����\n" NOR 
        HIM "������Ѩ�ɹ������������Ч����\n" NOR,
        HIY "������ʱ�����ܵ������·�ʲôǣ���ŷ��Ŀ�ʼ��������ӿ�룬\n" NOR 
        HIY "�Ծ��˵��ٶȷɿ�Ĵ�����Ѩ���ؿ�ʼ�޸��𻵵ľ�����˲���ھ���\n" NOR 
        HIY "��㱼���·�о��ص���ĸ�׵Ļ���㣬���̲�סϮ���ľ��⣬����\n" NOR 
        HIY "��˯����ȥ��������\n" NOR,
        HIG "�峿������������ɢ��������Ψ�д��һƬ�ž�����������\n" NOR,
        HIR "�㷢�����ڵ���������𾪣���Ȼ�����Ѿ����˽����ɣ�����ȴ����\n" NOR
        HIR "����Ϣ��ȡ֮��������֮���꣬����Ҳ���ؿ��˼���������ü������\n" NOR 
        HIR "��һС����ɫ̥�ǣ���ϸ�۲�Ļ����ᷢ�����̥����ͬһ�ѵ�����\n" NOR 
        HIR "����һ�㣬ɢ��������ɷ��֮���������������ӣ���������������\n" NOR 
        HIR "��Ƥһ�㣬ϡ�ﻩ���ĵ��²����ϻ���Ƥ��������Щ�����Ƥ�����\n" NOR 
        HIR "��������ǰ���ӵİ��ۡ�\n\n" NOR,
});

string get_jieti_place()
{
        string file;
        
        file = domain_file(base_name(this_object()));
        
        return file;
}

int do_jieti();
int do_decide();
void jieti_player(object me);

int do_jieti()
{
        object me;
        string msg, place;
        
        me = this_player();
        if (! ultrap(me) || ! me->query("animaout"))
                return notify_fail("�㻹û���޳�ԪӤ������������ħ���壿\n");
        
        if ((int)me->query_skill("martial-cognize", 1) < 400)
                return notify_fail("�����ѧ����û�дﵽ�İټ���������ħ���壬�����߻���ħ��\n");

        if (me->query("combat_exp") < 100000000)
                return notify_fail("��ľ��黹������óȻ��ħ���壬���߻���ħ�ġ�\n");

        if (me->query("couple"))
                return notify_fail("����ǰ���㻹�ǰѼ���ĺ��֮�ǽ�����ɡ�\n");

        if (me->query("bunch"))
                return notify_fail("����ǰ���㻹�ǰѰ��ɵĺ��֮�ǽ�����ɡ�\n");

        if (me->query("brothers"))
                return notify_fail("����ǰ���㻹�ǰѽ���ĺ��֮�ǽ�����ɡ�\n");

        if (me->query("league"))
                return notify_fail("����ǰ���㻹�ǰ����˵ĺ��֮�ǽ�����ɡ�\n");

        place = get_jieti_place();

        if (me->query("jieti/" + place))
        {
                if ((int)me->query("jieti/times") < 5 || place != "songshan")
                        return notify_fail("���Ѿ��ڴ˽�����������˴˵ص����ݼ����\n");
        }
        
        if (place == "songshan" && (int)me->query("jieti/times") < 4)
                return notify_fail("������ɽ����߲�ε���ħ���壬�㻹û�дﵽ������磡\n");

        msg = HIY "��ħ������һ�ֺķѴ����ľ��顢�似�������л���ѧ����ķ�ʽ��ͨ����ħ\n" +
                  "���壬���Դ�������������ʣ��������������ʡ��������ޡ��������ޡ���\n" +
                  "���������Ǳ������õ��ܴ����ߣ���ս���е�ɱ����Ҳ����ļ�ǿ����\n" +
                  "�Ƿ�ȷ��(decide)�Լ���������ħ���壿\n" NOR;

        me->set_temp("attempt_jieti", place);
        tell_object(me, msg);
        return 1;
}

int do_decide()
{
        string place;
        object me = this_player();
        
        if (! stringp(place = me->query_temp("attempt_jieti")))
                return notify_fail("�������ʲô��\n");

        if (place != get_jieti_place())
                return notify_fail("�������ʲô��\n");

        tell_object(me, HIW "���Ŀ��˼�����ã������¶����ģ�������ħ���壡��\n\n" NOR);
        me->delete_temp("attempt_jieti");
        call_out("jieti_msg", 0, me, 0, place);
        return 1;
}

void jieti_player(object me)
{
        mixed files;
        string special;
        string msg, place;
        string *skills;
        mapping all_skills;
        int i;
        
        place = get_jieti_place();
        
        if (me->query("gender") == "����")
                me->set("gender", "����");   
                             
        me->set("score", 0);
        me->set("shen", 0);
        me->set("mud_age", 0);
        me->set("age", 14); 
        me->set("birthday", time());
        me->delete("weiwang");        
        me->delete("meili");
        me->delete("balance");
        me->delete("total_hatred");
                
        me->set("combat_exp", 10000000);
        me->set("potential", 1000000);
        me->set("learned_points", 0);
        me->set("experience", 100000);
        me->set("learned_experience", 0);
        me->set("magic_points", 20000);        
        me->set("level", 100);

        me->set("max_neili", 5000);
        me->set("max_qi", 2000);
        me->set("max_jing", 1000);
        me->set("max_jingli", 2000);
        me->set("eff_qi", me->query("max_qi"));
        me->set("qi", me->query("eff_qi"));
        me->set("eff_jing", me->query("max_jing"));
        me->set("jing", me->query("eff_jing"));
        me->set("eff_jingli", me->query("max_jingli"));
        
        me->delete("couple");                // ��ͥ��¼
        me->delete("sex");                   // ������¼
        me->delete("brothers");              // ����ֵ�
        me->delete("bunch");                 // ���ɼ�¼
        me->delete("league");                // ͬ�˼�¼    
        me->delete("family");                // ���ɼ�¼
        me->delete("class");                 // �ƺż�¼
        me->delete("detach");                // ��ʦ��¼
        me->delete("betrayer");              // ��ʦ��¼
        me->delete("long");                  // ��������
        me->set("title", "��ͨ����");        // ���˳ƺ�
        me->set("character", "��ʿ��˫");    // �����Ը�
        me->delete("combat");                // PK  ��¼          
        me->delete("animaout");              // ԪӤ����     
        me->delete("breakup");               // �ζ�����
        me->delete("can_learn");             // ���¼�¼
        me->delete("can_make");              // ��ҩ��¼
        me->delete("degree");                // �ٸ�ְλ
        me->delete("degree_jungong");        // ������¼
        me->delete("gift");                  // �Ե���¼
        me->delete("guo_shoucheng");         // �سǼ�¼
        me->delete("opinion");               // ���ۼ�¼
        me->delete("opinions");              // ��ʦ���
        me->delete("out_family");            // ��ʦ����
        me->delete("pawns");                 // �䵱��¼
        me->delete("task");                  // ʹ������
        me->delete("quest_count");           // ��������
        me->delete("questdg_times");         // ��ʦ����
        me->delete("quesths_times");         // ��ʦ����
        me->delete("questkh_times");         // ��ʦ����
        me->delete("questsn_times");         // ��ʦ����    
        me->delete("map");                   // ��ͼ��־
        me->delete("rumor");                 // �¼���¼
        me->delete("schedule");              // �ƻ���¼
        me->delete("see_feng");              // ��������
        me->delete("skybook");               // �����¼
        me->delete("sl");                    // �����书
        me->delete("sl_gifts");              // �����书
        me->delete("luohan_winner");         // ʮ���޺���
        me->delete("story");                 // �еĹ���
             
        all_skills = me->query_skills();
        skills = keys(all_skills);
        
        for (i = 0; i < sizeof(skills); i++)
        {
                if (all_skills[skills[i]] > 400 &&
                    SKILL_D(skills[i])->type() != "knowledge")
                        me->set_skill(skills[i], 400); 
               
                if (all_skills[skills[i]] < 400 &&
                    skills[i] != "zuoyou-hubo")
                        me->delete_skill(skills[i]);
        } 
        
        /*        
        me->set_skill("martial-cognize", 1000); 
        me->set_skill("count", 1000);
        me->set_skill("mathematics", 1000);
        */
        me->set_skill("literate", 1000);
        me->add("jieti/times",1);
        me->set("jieti/" + place, 1);
        
        if (me->is_ghost()) me->reincarnate();
        me->reset_action(); 
                
        msg = HIG "���õĽ��弼���У�" NOR;

        // �鿴���е����⼼���ļ�
        files = ({ "bian", "dispel", "drift", "ghost", 
                   "jin", "sheng", "yuan", 
                });
        
        for (i = 0; i < sizeof(files); i++)
        {
                if (me->query("special_skill/" + files[i]))
                        files[i] = 0;
        }
        
        files -= ({ 0 });
        
        // ��õ�һ���
        special = files[random(sizeof(files))];
        me->set("special_skill/" + special, 1);
        msg += SPECIAL_D(special)->name();
        
        message("channel:rumor", HIM "����ħ���塿" + me->query("name") +
                "��ý��弼��--" + SPECIAL_D(special)->name() + HIB "��\n" NOR, users());    
                
        files -= ({ special });
        
        if (sizeof(files) && random(21) == 1) 
        {      
                // ��õڶ����                             
                special = files[random(sizeof(files))];
                me->set("special_skill/" + special, 1);
                msg += HIG "��" NOR + SPECIAL_D(special)->name();

                message("channel:rumor", HIM "����ħ���塿" + me->query("name") +
                        "��ý��弼��--" + SPECIAL_D(special)->name() + HIB "��\n" NOR, users());    
        }
        
        me->set("special_skill/shuang", 1);
        
        msg += HIG "��" NOR + HIY "��ʿ��˫" NOR;       
        msg += HIG "��\n" NOR;
                                                         
        tell_object(me, msg);
}

void jieti_msg(object me, int stage, string place)
{
        string msg;

        if (stage == 5) me->revive();

        msg = HIR + jieti_msg[stage] + NOR;
        tell_object(me, HIY + msg + NOR);
        if (stage < sizeof(jieti_msg) - 1)
        {
                if (stage == 4) me->unconcious();

                stage++;
                call_out("jieti_msg", 1, me, stage, place);
        } else
        {
                jieti_player(me);
                CHANNEL_D->do_channel(this_object(), "rumor", "��˵" + me->name(1) +
                                      "��" + this_object()->short() + "��ħ�����ˣ�");
        }      
        return;
}
