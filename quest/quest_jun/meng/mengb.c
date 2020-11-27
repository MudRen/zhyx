// Updated by Lonely

inherit NPC;

#include <room.h>
#include <ansi.h>
#include <command.h>

mapping way = ([ 
        "/quest/quest_jun/mying1"   :     "south",
        "/quest/quest_jun/mying"    :     "south",
        "/quest/quest_jun/myuanmen1":     "south",
        "/quest/quest_jun/caoyuan4" :     "south",
        "/quest/quest_jun/caoyuan3" :     "west",
        "/quest/quest_jun/caoyuan2" :     "west",
        "/quest/quest_jun/caoyuan1" :     "west",
        "/quest/quest_jun/caoyuan"  :     "west", 
        "/quest/quest_jun/shanlu3"  :     "west",
        "/quest/quest_jun/dhunya"   :     "south",
        "/quest/quest_jun/shanlu2"  :     "south", 
        "/quest/quest_jun/wsling"   :     "south",
        "/quest/quest_jun/shanlu1"  :     "south", 
        "/quest/quest_jun/shanlu"   :     "south", 
        "/quest/quest_jun/conglin1" :     "south", 
        "/quest/quest_jun/conglin2" :     "south", 
        "/quest/quest_jun/conglin3" :     "west", 
        "/quest/quest_jun/conglin4" :     "west", 
        "/quest/quest_jun/syuanmen1":     "south", 
        "/quest/quest_jun/sying"    :     "south", 
]);

void attack_over(object me);
varargs void attack_begin(object me, object target, object room, object env, string dir);
void check_me(object me);
void move_me(object me);

int do_kill(string arg);
int get_exp_rate();
int get_level(int exp);   

void create()
{
        int lvl, skill, nl, exp;

        set_name("�������",({ "menggu junguan", "junguan" }) );
        set("gender", "����" );
        set("long","����һ��������٣������ž���ִ����ս������\n");

        set("int", 30);
        set("str", 30 + random(20));
        set("con", 20 + random(20));
        set("dex", 20 + random(20));
        set("age", 20 + random(30));  
        set("per", 15 + random(15));                                         
        
        exp = get_exp_rate() / 2;
        skill = get_level(exp);
        
        skill += 100;
        
        set("combat_exp", exp);       
        nl = skill * 10 + exp / 10000;
        
        set("max_neili", nl);
        set("neili", query("max_neili") * 3 / 2); 
        set("max_jingli", nl);
        set("jingli", query("max_jingli"));
        set("max_qi", nl * 10);
        set("qi",  query("max_qi"));
        set("eff_qi", query("max_qi"));
        set("max_jing", nl);
        set("eff_jing", query("max_jing"));
        set("jiali", skill / 2); 

        set_skill("longxiang-banruo", skill);
        set_skill("xuedao-daofa", skill);
        set_skill("shenkong-xing", skill);
        set_skill("dashou-yin", skill);
        set_skill("hand", skill);
        set_skill("force", skill);
        set_skill("dodge", skill);
        set_skill("blade", skill);
        set_skill("parry", skill);
        set_skill("arrow", skill*2/3);

        map_skill("force", "longxiang-banruo");
        map_skill("dodge", "shenkong-xing");
        map_skill("hand", "dashou-yin");
        map_skill("parry", "xuedao-daofa");
        map_skill("blade", "xuedao-daofa");   

        prepare_skill("hand", "dashou-yin");   
        set_temp("jun_quest/party", "meng"); 
        set_temp("quest_ob", 1); 
        set("no_get", 1);     
        add_temp("apply/armor", 400);
        add_temp("apply/damage", 100);
        setup();

        lvl = (query("str") + skill / 10) / 10 - 1;
        if (lvl > 8) lvl = 8;
        lvl = lvl - 2;
        if (lvl < 3) lvl = 3;
        carry_object("/quest/zhuzao/weapon/bow/bow"+lvl);
        carry_object(__DIR__"obj/wandao");
        carry_object("/quest/zhuzao/weapon/bow/bow"+lvl);
        carry_object(__DIR__"obj/wandao");    
        carry_object("/quest/zhuzao/weapon/bow/bow"+lvl);
        carry_object(__DIR__"obj/wandao");    
        carry_object("/quest/zhuzao/weapon/bow/bow"+lvl);
        carry_object(__DIR__"obj/wandao");    
        carry_object(__DIR__"obj/wandao")->wield();
        carry_object(__DIR__"obj/tiejia")->wear();   
        carry_object(__DIR__"obj/pifeng")->wear();  
        // carry_object(__DIR__"horse")->ride();
}

void change_ob()
{ 
        int jungong, jiang;
        object horse;
        
        jungong = 4 + random(query("combat_exp") / 5000000 + 1);
        if (jungong > 12) jungong = 12;

        add("eff_qi", jungong * 2000);
        set("qi", query("eff_qi"));
        set_temp("jun_quest/group", jungong);
        set("degree_jungong", jungong);

        if (jungong > 10) set("title", HIR "�������" NOR);
        else if (jungong > 8) set("title", HIG "�������" NOR);
        else if (jungong > 5) set("title", HIY "����ӳ�" NOR);
        else set("title", HIC "���С�ӳ�" NOR);

        
        set_temp("jun_quest/last_move", "/quest/quest_jun/mying1");
        
        horse = new(__DIR__"horse");
        if (horse->move(environment(this_object()))) 
                "/cmds/std/ride"->main(this_object(), horse->query("id"));    
        else destruct(horse); 
        
        remove_call_out("check_me");
        remove_call_out("move_me");
        call_out("move_me", 2, this_object());
        call_out("check_me", 2, this_object());    
        return;
}

void move_me(object me)
{
        mapping move_way;
        string site;
        object room;

        if (! objectp(me)) return;
        
        move_way = way;
        room = environment(me);
        site = file_name(room);


        if (site == "/quest/quest_jun/sying1")  
        {
                if (! me->query_temp("jun_quest/attacking"))
                {
                        remove_call_out("move_me");  
                        message("channel:rumor", MAG "\n����ʷ���ء���"
                                + CHINESE_D->chinese_date((time() - 14*365*24*60*60))
                                + MAG "�������������ξ�����������\n" NOR, users()); 
                                
                        WAR_D->fail_war();
                        return;
                }  
                remove_call_out("move_me"); 
                call_out("move_me", 4, me); 
                return;
        }

        if (site == "/quest/quest_jun/syuanmen1")
        {
                if (room->query("defence") > 0 && ! me->query_temp("jun_quest/break"))
                {
                        message("channel:rumor", MAG "\n�����߾��顿���Σ�һ��" 
                                + me->query("title") + MAG "����Ľ��ͻ����Ѿ������ξ���Ӫ��"
                                + "�ξ��Խ���������Ԯ������\n" NOR, users());
                }

                if (room->query("defence") > 0)
                {
                        me->set_temp("jun_quest/break", 1);
                        command("break");
                        remove_call_out("move_me");
                        call_out("move_me", 4, me);
                        return;
                } else
                if (me->query_temp("jun_quest/break"))
                {
                        message("channel:rumor", MAG "\n�����߾��顿���Σ��ξ���Ӫ"
                                + MAG "������������ƣ�����Σ��������\n" NOR, users());  
                        me->delete_temp("jun_quest/break");
                } 

        }

        if (! living(me) || me->is_fighting() || me->is_busy() 
        ||  me->query_temp("jun_quest/attacking"))
        {
                remove_call_out("move_me");
                call_out("move_me", 4, me);
                return;
        }                    

        if (move_way[site])
        {
                me->set_temp("jun_quest/last_move", site);
                me->command("go " + move_way[site]);
        } else
        if (me->query_temp("jun_quest/last_move"))
                me->move(me->query_temp("jun_quest/last_move"));

        message_vision(
                HIB "$N������һ֧����ͻ��������س��ξ���Ӫ�ƶ���.....\n", me);
                me->start_busy(2 + random(2));
                remove_call_out("move_me");
                call_out("move_me", 4, me);
                return;
}

void die()
{
        object ob;
        
        remove_call_out("move_me");
        remove_call_out("check_me");
        if (objectp(ob = query_last_damage_from())) 
                ob->add_temp("jun_quest/reward", 10);

        message_vision("$N����Ľ�������ڼ����翹�����ڱ�����" +
                        HIR "������" NOR "��\n",
                        this_object());
        destruct(this_object());
        return;
}

#include "attack.h"
