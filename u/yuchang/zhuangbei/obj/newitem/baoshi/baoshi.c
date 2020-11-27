#include <ansi.h>
inherit ITEM;

void create()
{
        set_name("ԭʯ", ({"baoshi","yuanshi"}));
        set_weight(500);
       set("changed",1);
                  set("no_sell",1);
                 set("unit","��");
                 set("material","baoshi");
                 set("color",0);
                 set("value",1);
                 set("long","һ��ԭʯ��������ĳ���ط��������Ƴɱ�ʯ�ġ�\n");
        if( clonep() )
                set_default_object(__FILE__);
        setup();
}

void init()
{
	add_action("do_enchase", "inset");
}

int do_enchase(string arg)
{
   object in_obj;
   string item,weapon_type;
   string mats;
   mixed *list_prop;
   int rd,inset_num ,i,k,tmp;
   object me = this_player();
   object ob = this_object();
   mapping prop;
   string *attack_kind=({"cold","fire","lightning","poison","magic"});
   
   if(ob->query("level")<1) return notify_fail("������������аɣ�\n");
   if(!arg) return notify_fail("��Ҫ�ѱ�ʯ��Ƕ��ʲô�ϣ�\n");
   if(sscanf(arg, "%s", item)!=1) return notify_fail("��Ҫ�ѱ�ʯ��Ƕ��ʲô�ϣ�\n");
   if(!objectp(in_obj = present(item, me))) return notify_fail("������û������������\n");
   if( in_obj->query("equipped") )
      return notify_fail("����������������������Ƕ��ʯ��\n");
   if( in_obj->query("sockets/max")<=in_obj->query("sockets/now"))
      return notify_fail("��������������Ƕ��ʯ���Ѿ������ˡ�\n");
   
   if (random(100)>85) {
       message_vision(CYN"$N��$n"+CYN"��"+in_obj->query("name")+CYN"ʹ��һͱ�� \n"NOR,me,ob);
       tell_room(environment(me),HIM"ֻ��"+ob->name()+HIM"ײ��"+in_obj->query("name")+HIM"�ϣ�ƬƬ�ѿ��� \n"NOR);
       message_vision(CYN"$N��Ƕ$nʧ���ˡ�\n"NOR,me,ob);
       ob->move(VOID_OB);
       destruct(ob); 
       return 1;
   }
   if (random(100)>85) {
       message_vision(CYN"$N��$n"+CYN"��"+in_obj->query("name")+CYN"ʹ��һͱ�� \n"NOR,me,ob);
       tell_room(environment(me),HIM"���"+ob->name()+HIM"��"+in_obj->query("name")+HIM"����ͱ��һ��������� \n"NOR);
       message_vision(HIM+in_obj->query("name")+"���ˡ�\n"NOR,me,ob);
       message_vision(CYN"$N��Ƕ$nʧ���ˡ�\n"NOR,me,ob);
       in_obj->move(VOID_OB);
       destruct(in_obj); 
       return 1;
   }
   if (random(100)>85) {
       message_vision(CYN"$N��$n"+CYN"��"+in_obj->query("name")+CYN"ʹ��һͱ�� \n"NOR,me,ob);
       tell_room(environment(me),HIM"ֻ��"+ob->name()+HIM"ײ��"+in_obj->query("name")+HIM"�ϣ�ƬƬ�ѿ��� \n"NOR);
       tell_room(environment(me),HIM+in_obj->query("name")+HIM"Ҳ��ͱ��һ��������� \n"NOR);
       message_vision(HIM+ob->name()+"��"+in_obj->query("name")+"���������ˡ�\n"NOR,me,ob);
       message_vision(CYN"$N��Ƕ$nʧ���ˡ�\n"NOR,me,ob);
       ob->move(VOID_OB);
       in_obj->move(VOID_OB);
       destruct(ob); 
       destruct(in_obj); 
       return 1;
   }      
   
   prop=ob->query("prop");
   list_prop=keys(prop);
   list_prop = sort_array(list_prop, "sort_keys", ob);   
   if(in_obj->query("armor_prop"))   //����
   {
      for (i=0;i<sizeof(list_prop);i++)
       {
       	  switch(list_prop[i]) {
       	  	case "damage":
       	  		tmp=in_obj->query("armor_prop/armor");
       	  		in_obj->add("armor_prop/armor",(int)(prop["damage"]*tmp/100));
       	  		break;
       	  	case "luck" :if (random(40) < prop["luck"]) in_obj->add("sockets/max",1);break;
       	  	case "attack":
       	  	        in_obj->add("armor_prop/"+attack_kind[random(5)]+"_defence",ob->query("level")*4);
       	  		break;	
       	  }
       }
   }
   else if(in_obj->query("weapon_prop")) 
   {  
      for (i=0;i<sizeof(list_prop);i++)
       {
       	  switch(list_prop[i]) {
       	  	case "damage":
       	  		tmp=in_obj->query("weapon_prop/damage");
       	  		in_obj->add("weapon_prop/damage",(int)(prop["damage"]*tmp/100));
       	  		break;
       	  	case "luck" :if (random(40) < prop["luck"]) in_obj->add("weapon_prop/luck",1);break;
       	  	case "attack":
       	  	        for (k=0;k<4;k++) {
       	  			if (in_obj->query("weapon_prop/"+attack_kind[k]+"_attack")) {if (random(40)<prop["attack"]) in_obj->add(attack_kind[k]+"_attack/max_level",1);}
       	  		} break;	
       	  }
       }
     }
       in_obj->add("sockets/now",1);
       message_vision(CYN"$N��$n"+CYN"��Ƕ��"+in_obj->query("name")+CYN"�� \n"NOR,me,ob);
       tell_room(environment(me),HIM"ֻ��"+ob->name()+HIM"����һ�����޵Ĺ�â,������"+in_obj->query("name")+HIM"����Χ \n"NOR);
       message_vision(CYN""+in_obj->query("name")+CYN"�ƺ���ø��������ˣ�\n"NOR,me);
       if(!in_obj->query("old_long")) in_obj->set("old_long",in_obj->query("long"));
       in_obj->set("long",in_obj->query("old_long")+"����Ƕ����"HIW+chinese_number(in_obj->query("sockets/now"))+"�ű�ʯ\n"NOR);
       in_obj->save();
       destruct(ob);
       return 1;
}
