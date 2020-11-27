// stone.c
// ALN Sep / 97 
// Modified by haiyan

inherit ROOM;
#include <ansi.h>

string *practice_types = ({
        "blade",
        "club",
        "staff",
        "whip",
        "unarmed",
        "parry",
        "dodge"
});
        
int *cost(object, string);
void dropoff(object);

void create()
{
        set("short", "��ʯ");
        set("long", @LONG
��վ�������ϵľ�ʯ�ϣ�����ɽ��������ͷ�����ҡ���ʯҡҡ�λΣ���
�������У�˫������վ�����������ܣ�һƬ�ž�����ʯ������������Ԩ���ƺ�
�ڴ˺�����������
LONG);

        set("outdoors", "shenlong");
        set("cost", 10);
        setup();
}

void init()
{
        object me = this_player();
        int lvl = (int)me->query_skill("dodge", 1);

        if( interactive(me) && !random(lvl) )
        {
            call_out("dropoff", 1, me);             
            return;
        }

        add_action("do_practice",  "practice");
        add_action("do_practice",  "lian");
        add_action("do_jump", "jump");
}

int do_practice(string arg)
{
        object weapon, me = this_player();
        string skillarg, str, multiple;
        int w, *cost, times;

        if( me->is_busy() )
        {
                tell_object(me, "��������æ���ء�\n");
                return 1;
        }

        if( me->is_fighting() )
        {
                tell_object(me, "���Ѿ���ս�����ˣ�ѧһ��ʵս����ɡ�\n");
                return 1;
        }

        if( !arg ) return ("/cmds/skill/enable")->main(me, arg);

        if(sscanf(arg, "%s %d", skillarg, times) != 2 )
                skillarg = arg;

        if( (w = member_array(skillarg, practice_types)) == -1 )
        {
                tell_object(me, "����ܲ����������ϰ��\n");
                return 1;
        }

        if( w < 4 )
        {
                if( !objectp(weapon = me->query_temp("weapon")) )
                {
                        tell_object(me, "��û����������ô��ϰ��\n");
                        return 1;
                } else
                if( weapon->query("skill_type") != skillarg )
                {
                        tell_object(me, "�����е��������ʺ���������ϰ�ļ��ܡ�\n");
                        return 1;
                }
        }

        if( (int)me->query_skill(skillarg, 1) < 30 )
        {
                tell_object(me, "�㻹����ȥ��ʦ����ѧѧ�ɡ�\n");
                return 1;
        }

        if( (int)me->query_skill(skillarg, 1) > 100 )
        {
                tell_object(me, "���Ѿ������������ʱ����ϰ������ˡ�\n");
                return 1;
        }                

        if(!times || times == 0) {
                times = 1;
                multiple="";
        }
        else    multiple="����";

        switch(skillarg)
        {
                case "blade"  : str = "����" + weapon->name();  break; 
                case "club"   : str = "����" + weapon->name();  break;
                case "staff"  : str = "����" + weapon->name();  break;
                case "whip"   : str = "����" + weapon->name();  break;
                case "unarmed": str = ""; break;
                case "parry"  : str = "�����ղ�"; break;
                case "dodge"  : str = "������Ծ"; break;
        }                
        message_vision("$N�ڿ����" + str + multiple + "��ϰ��" +
                       to_chinese(skillarg) + "��\n", me);

        for(times; times > 0; times--)
        {
                cost = cost(me, skillarg);
                if( (int)me->query("jing") < cost[0]
                    ||  (int)me->query("qi") < cost[1] )
                {
                        tell_object(me, "��ƣ������������������ֻ��ͣ��������\n");
                        return 1;
                }
                me->receive_damage("jing", cost[0]);
                me->receive_damage("qi", cost[1]);
                me->improve_skill(skillarg, random((int)me->query_int()));

                if( !random((int)me->query_skill("dodge", 1) + 30 ))
                {
                        dropoff(me);
                        return 1;
                }
        }
        return 1;
}

int do_jump(string arg)
{
        object me = this_player(), *inv = all_inventory(me);
        int mydodge = me->query_skill("dodge", 1);

        if( !arg || arg != "down" )
                return notify_fail("��Ҫ��������\n");

        tell_object(me, "������һ���������漴ֱ����ȥ��\n");
        message("vision", me->name() + "����������ȥ��\n", environment(me), me);
      
        if( random(mydodge) < 5 )
        {       
                me->receive_wound("jing", me->query("max_jing")/3 + random(me->query("max_jing")/2));
                me->receive_wound("qi", me->query("max_qi")/3 + random(me->query("max_qi")/2));

                for(int i = 0; i < sizeof(inv); i++)
                        if(!userp(inv[i]))   destruct(inv[i]);
                me->move("/d/shenlong/huangdao");
                message("vision", "�㷢��һ������ˮ���ܵļһﱻ��ˮ���ϰ��������ɵ��߽�һ����ԭ����" +
                        me->name() + "��\n", environment(me), me);
                me->unconcious();
                return 1;
        }

        me->move("/d/shenlong/sea");
        tell_object(me, "�㡰��ͨ�����뺣���ɬ�ĺ�ˮֱ����Ŀڱǹ��롣\n");
        message("vision", "ֻ��" + me->name() + "�Ӹߴ�����������\n", environment(me), me);
        return 1;
}

void dropoff(object me)
{
        object *inv = all_inventory(me);

        tell_object(me, "��ʯһ�Σ������㲻�ȵ��º����ˡ�\n");
        message("vision", me->name() + "ʧ�������ȥ��\n", environment(me), me);
        me->move("/d/shenlong/sea");
        tell_object(me, "һ�ɾ��������������㹾�๾�����˼��ں�ˮ��\n");
        me->unconcious();
        me->receive_wound("jing", me->query("max_jing")/3 + random(me->query("max_jing")/2));
        me->receive_wound("qi", me->query("max_qi")/3 + random(me->query("max_qi")/2));

        for(int i = 0; i < sizeof(inv); i++)
            if(!userp(inv[i]))   destruct(inv[i]);

        me->move("/d/shenlong/huangdao");
        message("vision", "�㷢��һ������ˮ���ܵļһﱻ��ˮ���ϰ��������ɵ��߽�һ����ԭ����" +
                me->name() + "��\n", environment(me), me);
}

int *cost(object ob, string skill)
{
     switch(skill)
     {
          case "blade"  : return ({10, 25});
          case "club"   : return ({15, 20});
          case "staff"  : return ({20, 15});
          case "whip"   : return ({30, 15});
          case "unarmed": return ({15, 30});
          case "parry"  : return ({10, 20});
          case "dodge"  : return ({20, 10});
     }
     return ({15, 15});
}

