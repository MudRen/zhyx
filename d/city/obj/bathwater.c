


#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "ǿЧ��ԡҺ" NOR, ({ "bath water", "muyu ye" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "\nһƿ������͸��Һ�壬��˵������ϴ���������е����������ͨ����use����ʹ�á�\n" NOR);
                set("unit", "��");
                set("value", 1000000);
                set("weight", 10);                
             }
        setup();
}

void init()
	{
		add_action("do_use","use");
	}
		

int do_use( string arg )
{		
	 string mapsk;	 
	 object me;

        if ( ! arg || (arg != "bath water" && arg != "muyu ye") )
          return 0;
	
	      me = this_player();
	      
	      if (me->query("tattoo/chest_long")=="����ڤ��վ���������׹Ƕ�֮�ϣ�����ԩ��Χ������")
	      	me->delete("special_skill/hatred/");
	      if (me->query("tattoo/chest_long")=="�����������໥���Ʋ�������������")
	      	me->delete("special_skill/power/");
	      if (me->query("tattoo/chest_long")=="һֻԡ�����������Ƽ䣬���˳���")
	      	me->delete("special_skill/wrath/");
	      if (me->query("tattoo/chest_long")=="����ɮ�˳��ݷ��棬���ɢ������ʥׯ��")
	      	me->delete("special_skill/health/");
	      if (me->query("tattoo/chest_long")=="�ٹ�ҹ�У�����ԩ�갧�����ޣ�����ë���Ȼ")
	      	me->delete("special_skill/agile/");
	      if (me->query("tattoo/chest_long")=="����������վ����������֮�£���������")
	      	me->delete("special_skill/ironskin/");
	      if (me->query("tattoo/chest_long")=="��ȴ󱯹��������������˱�������ǧ֧����̬����")
	      	me->delete("special_skill/might/");
	      if (me->query("tattoo/chest_long")=="���ｭɽ������׳�������ƻֺ����֮��")
	      	me->delete("special_skill/mystery/");
	      if (me->query("tattoo/chest_long")=="�����乭������Ÿ�̫������ڿ���")
	      	me->delete("special_skill/self/");
	      if (me->query("tattoo/chest_long")=="�����������ڰ˱������ϣ�������ϼ���ƣ��ƻ�����")
	      	me->delete("special_skill/herb/");
	      	
	      if (me->query("tattoo/back_long")=="����ڤ��վ���������׹Ƕ�֮�ϣ�����ԩ��Χ������")
	      	me->delete("special_skill/hatred/");
	      if (me->query("tattoo/back_long")=="�����������໥���Ʋ�������������")
	      	me->delete("special_skill/power/");
	      if (me->query("tattoo/back_long")=="һֻԡ�����������Ƽ䣬���˳���")
	      	me->delete("special_skill/wrath/");
	      if (me->query("tattoo/back_long")=="����ɮ�˳��ݷ��棬���ɢ������ʥׯ��")
	      	me->delete("special_skill/health/");
	      if (me->query("tattoo/back_long")=="�ٹ�ҹ�У�����ԩ�갧�����ޣ�����ë���Ȼ")
	      	me->delete("special_skill/agile/");
	      if (me->query("tattoo/back_long")=="����������վ����������֮�£���������")
	      	me->delete("special_skill/ironskin/");
	      if (me->query("tattoo/back_long")=="��ȴ󱯹��������������˱�������ǧ֧����̬����")
	      	me->delete("special_skill/might/");
	      if (me->query("tattoo/back_long")=="���ｭɽ������׳�������ƻֺ����֮��")
	      	me->delete("special_skill/mystery/");
	      if (me->query("tattoo/back_long")=="�����乭������Ÿ�̫������ڿ���")
	      	me->delete("special_skill/self/");
	      if (me->query("tattoo/back_long")=="�����������ڰ˱������ϣ�������ϼ���ƣ��ƻ�����")
	      	me->delete("special_skill/herb/");
	 
	      me->delete("tattoo/special/");
	      
	      me->delete("tattoo/tattoo_str");
	      me->delete("tattoo/tattoo_con");
	      me->delete("tattoo/tattoo_int");
	      me->delete("tattoo/tattoo_dex");
	      me->delete("tattoo/tattoo_per");
	      
	      me->delete("tattoo/face_long");
	      me->delete("tattoo/chest_long");
	      me->delete("tattoo/back_long");
	      me->delete("tattoo/leftarm_long");
	      me->delete("tattoo/rightarm_long");
	      me->delete("tattoo/buttock_long");
	      
	      me->delete("tattoo/tattoo");   
	      
        message_vision(HIG "$N"HIG"����ԡҺĨ�����ϣ�Ƥ������ת�ȣ��ٶ���û��հ�ľ�ʹ......\n" NOR, me); 
        
        me->unconcious();

		destruct(this_object());
      return 1;
}

string query_autoload()
{
        if ( ! query("owner") )
                return 0;

        return query("owner");
}

void autoload(string owner)
{       
     if (owner) set("owner", owner);
}


		


       	