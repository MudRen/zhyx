
//��̥����(��ɷ����ר����Ʒ���Ժ����µ����츳��

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "��̥������" NOR, ({ "tuotai wan", "wan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", CYN "һ�ź������ҩ�衣��set��eat��"+
                                "��˵��ɷ���Ƿ�ʳ�������µ����츳��\n" NOR);
                set("unit", "��");
                set("value", 10);
                set("no_sell",1);
                set("weight", 10);                
             }
        setup();
}

void init()
        {       
                add_action("do_choose","choose");
                add_action("do_eat","eat");
        }
                
int do_choose(string arg)
{
    object me;
    int tmpstr, tmpint, tmpcon,tmpdex;
    string answer;

    me = this_player();

    if	( ! me->query("special_skill/lonely") ) return 0;

    if( !arg || sscanf(arg, "%d %d %d %d", tmpstr, tmpint, tmpcon,tmpdex)!=4 )
                return notify_fail(HIG"ָ���ʽ��choose <����> <����> <����> <��>\n"NOR);
 
    if( tmpstr<13) return notify_fail("����ѡ���������������С��13��\n");
    if( tmpint>30) return notify_fail("����ѡ������Բ������ܴ���30��\n");
    if( tmpint<13) return notify_fail("����ѡ������Բ�������С��13��\n");
    if( tmpcon>30) return notify_fail("����ѡ��ĸ��ǲ������ܴ���30��\n");
    if( tmpcon<13) return notify_fail("����ѡ��ĸ��ǲ�������С��13��\n");
    if( tmpdex>30) return notify_fail("����ѡ������������ܴ���30��\n");
    if( tmpdex<13) return notify_fail("����ѡ�������������С��13��\n");
    if((tmpstr+tmpint+tmpcon+tmpdex)>80) 
    return notify_fail("����ѡ��Ĳ����ܺͲ��ܴ���80��\n");
    write(HIC "ָ���츳Ϊ ����:" + tmpstr + " ����:" + tmpint + " ����:" +
          tmpcon + " ��:" + tmpdex + "��\n���ԵĻ���(eat wan)��\n"NOR, me);

    me->set_temp("/lonely/tuotai/str",tmpstr);
    me->set_temp("/lonely/tuotai/int",tmpint);
    me->set_temp("/lonely/tuotai/con",tmpcon);
    me->set_temp("/lonely/tuotai/dex",tmpdex);   
    return 1;
}

int do_eat(string arg)
{
   object me;
   mapping my, my_sk;
   string skills_name;

   me = this_player();
   my = me->query_entire_dbase();
   my_sk = me->query_skills();

   if ( ! arg || ( arg != "tuotai wan" && arg != "wan") ) 
       return 0;

   if ( ! me->query("special_skill/lonely") ) 
   {
      write(HIR"ֻ����ɷ���ǲ��ܳ���̥�����裡\n"NOR);
      return 1;
   }

   if ( ! me->query_temp("/lonely/tuotai/") )
   {
      write(HIR"������chooseѡ����Ҫ�������������츳��\n"NOR);
      return 1;
   }
	 	
   message_vision(HIR "$Nһ������������̥�����裬��ʱ�е�ͷʹ���ѣ�"   
                         "�಻���ԡ�\n"NOR, me);

   my["str"] = me->query_temp("/lonely/tuotai/str");
   my["int"] = me->query_temp("/lonely/tuotai/int");
   my["con"] = me->query_temp("/lonely/tuotai/con");
   my["dex"] = me->query_temp("/lonely/tuotai/dex");

   me->set("combat_exp", 0);           
   me->set("max_neili",0);
   me->set("neili",0);
   me->set("max_jingli",0);
   me->set("jingli",0);
   me->set("max_qi",100);
   me->set("eff_qi",100);
   me->set("qi",100);
   me->set("max_jing",100);
   me->set("eff_jing",100);
   me->set("jing",100);
    me->set("mud_age",0);
    me->set("age", 14);
    me->set("shen",0);
    me->delete("breakup");
    me->delete("animaout");

   foreach(skills_name in keys(my_sk))
   {
       me->delete_skill(skills_name);
   }

   me->delete("gift");
   me->delete_temp("lonely");     
   me->set("lonely/tuotai",1);
   me->unconcious();
   me->set("potential", me->query_potential_limit() );

   destruct(this_object()); 
   return 1;
}

int query_autoload() 
{ return 1; }


        
