#include <ansi.h>

inherit ROOM;
string look_tiaofu();
#define JINYONG   "/u/sanben/leitai/jinyong"

void create()
{
	set("short", HIY"��ɽ�۽�--�����ַ�����̨"NOR);
	set("long", 
HIW"�˵ر�����ս����������֮�������������ڴ˴���\n"
"�������ֱ��ȡ����֮���������һ�ֻ��ǽ������\n"
"һ��" NOR HIG"����(tiaofu)" NOR HIW"��������֮�˶����ȿ������������\n"NOR);	
       set("biwutai",1);      
       set("no_sleep_room",1);
       set("no_steal",1);
       set("no_beg",1);
       set("no_get_from",1);
       
	set("item_desc", ([
		"tiaofu" : (: look_tiaofu :),
	]));

       set("exits", ([ 
               "down" : "/d/city/wumiao2", 
       ]));

	set("objects", ([
		__DIR__"jinyong": 1,
	]));
	setup();
}

string look_tiaofu()
{
    object jy;
    string msg;
    
    jy = find_object(JINYONG);
    if ( ! jy ) jy = load_object(JINYONG);

    msg = "===================================================\n";
    msg += HIR"�������һ�ν�����ʮ���ƽ����ӹ����,\n";
    msg += "ÿ�δ����޶�ʮ���ӣ���ʱ����\n\n"NOR;

    msg += HIG"Ŀǰ���������а����£�\n";
    msg += "��һ���֣�����ͨ    " + jy->query("namelist/5") + 
           "(" + jy->query("idlist/5") + ")\n"; 
    msg += "�ڶ����֣���  ؤ    " + jy->query("namelist/4") + 
           "(" + jy->query("idlist/4") + ")\n"; 
    msg += "�������֣���  ��    " + jy->query("namelist/3") + 
           "(" + jy->query("idlist/3") + ")\n"; 
    msg += "���ĸ��֣���  ��    " + jy->query("namelist/2") + 
           "(" + jy->query("idlist/2") + ")\n"; 
    msg += "������֣���  а    " + jy->query("namelist/1") + 
           "(" + jy->query("idlist/1") + ")\n"NOR; 

    msg += HIY"\n����Ӯ��̨��ɰ����¸�ʽ��������\n"NOR;
    msg += HIC"Ϊ�������ñ�����ʽΪ��\n";
    msg += "setwp ��������\n";
    msg += "���õı���������\n"
           "�����������ޡ����ơ�������������ָ�ס��ȡ��е�һ�֡�\n"NOR;
    msg += HIW"Ϊ�������þ��еĸ�ʽΪ��\n";
    msg += "setpfm ��������|��������|��������\n";
    msg += "���磺setpfm taixuan-gong|unarmed|xuan\n"NOR;
    msg += "==================================================\n";
    return msg;
}

int no_die(object me)
{               
        message_vision (HIC"ֻ���������ָ��$Nһָ��$N��ʱ�ָ��˾���\n"NOR,me);
        me->remove_all_enemy(1);
        me->revive();
        me->set("eff_qi",me->query("max_qi")); 
        me->set("eff_jing",me->query("max_jing"));               
        me->set("qi",me->query("eff_qi"));
        me->set("jing",me->query("eff_jing")); 
        me->clear_condition("poison");
        return 1;
}
