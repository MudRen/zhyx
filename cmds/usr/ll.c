// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */

#include <ansi.h>

inherit F_CLEAN_UP;

int look_item(object me, object obj);


void create() { seteuid(getuid()); }

int main(object me, string arg)
{
   object obj,target;
   int result;
   string id;

   if( !arg ) return notify_fail("��Ҫ�쿴ʲô��Ʒ��\n");
   obj=present(arg, me);
   if (!obj) obj = present(arg, environment(me));
   if (obj) return result = look_item(me, obj);
   else if (!wizardp(me)) return notify_fail("��Ҫ�쿴ʲô��Ʒ��\n");
   if (sscanf (arg, "%s in %s", arg, id) != 2) return notify_fail("��Ҫ�쿴ʲô��Ʒ��\n");
   target=find_player(id);
   if (!target)  return notify_fail("û�д����\n");
   obj=present(arg,target);
   if (obj) result = look_item(me, obj);
   else return notify_fail("����������û�д���Ʒ��\n");
   return result;
}



int look_item(object me, object obj)
{
   int i,j;
   mixed *inv;
   string text,*str,str1,msg;
   string *bind_type=({"����","װ����","ʰȡ��","ֱ�Ӱ�"});
   mapping tianfu=([
        "str":"��    ��",
        "con":"��    ��",
        "int":"��    ��",
        "per":"��    ò",
        "dex":"��    ��",
        "kar":"��    Ե",
                  ]);
   str=keys(tianfu);
   for (i=0;i<sizeof(tianfu);i++) {
                  j=obj->query("weapon_wiel/"+str[i]);
                  if (j>0) {str1=tianfu[str[i]];break;}
          }
                  
   
 //  if (obj->query("changed")<1 && obj->query("change")<1) return notify_fail("��ֻ��һ����ͨ��Ʒ��ûʲô�ÿ��ġ�\n");
    if (living(obj)) return notify_fail("����һ˫������"+obj->query("name")+"���ϱȻ��š���\n");
   if (obj->query("changed")<1 ) return notify_fail("��ֻ��һ����ͨ��Ʒ��ûʲô�ÿ��ġ�\n");
   if (obj->query("armor_prop") && obj->query("type") == "dazao")   {
                  msg=sprintf(HIM+"\n                    ��%22|s"+HIM+"��\n"+NOR,obj->short()); 
                  msg+=sprintf(HIM+repeat_string("��",34)+"\n"+NOR);
                  msg+=sprintf(HIM+"��"+NOR+HIR+"װ���ȼ��� "+HIM+chinese_number(obj->query("level"))+HIR+"����\n"+NOR);
                  msg+=sprintf(HIM+"��"+NOR+HIR+"�����Ṧ�������� "+HIM+obj->query("armor_prop/dodge")+"/30\n"+NOR);
                  msg+=sprintf(HIM+"��"+NOR+HIR+"��������������� "+HIM+obj->query("armor_prop/armor")+"/75\n"+NOR);
                  msg+=sprintf(HIM+"��"+NOR+HIR+"����ħ���������� "+HIM+obj->query("armor_prop/spells")+"/30\n"+NOR);
                  msg+=sprintf(HIM+"��"+NOR+HIR+"�����ڹ��ֿ����� "+HIM+obj->query("armor_prop/armor_vs_force")+"/700\n"+NOR);
                  msg+=sprintf(HIM+"��"+NOR+HIR+"����ħ���ֿ����� "+HIM+obj->query("armor_prop/armor_vs_spells")+"/700\n"+NOR);
                  msg+=sprintf(HIM+repeat_string("��",34)+"\n"+NOR);
   }
   else if (obj->query("weapon_prop"))
   {
                  for (i=0;i<sizeof(tianfu);i++) {
                          j=obj->query("weapon_wiel/"+str[i]);
                          if (j>0) {str1=tianfu[str[i]];break;}
                  }       
          
          msg=sprintf(HIM+"\n                    ��%22|s"+HIM+"��\n"+NOR,obj->short());
          msg+=sprintf(HIM+repeat_string("��",34)+"\n"+NOR);
          msg+=sprintf(HIM+"��"+NOR+HIR+"�������ԣ� "+HIM+"                                                     ��\n"+NOR); 
          msg+=sprintf(HIM+"��"+NOR+"\t"+HIC+"��    ����%10|d\t\t"+"��    ֵ��%10|d"+HIM+"      ��\n"+NOR,obj->query_weight(),obj->query("value"));
          msg+=sprintf(HIM+"��"+NOR+"\t"    +HIC+"�� �� �ȣ�%5|d"+"    \t\t"+"�� �� ����%10|d"+HIM+"      ��\n"+NOR,obj->query("consistence"),obj->query("weapon_prop/damage"));
          msg+=sprintf(HIM+"��"+NOR+"\t"+HIC+"�����ͣ�%-8s\t\t"+"�󶨣ɣģ�%-10s"+HIM+"      ��\n"+NOR,bind_type[obj->query("bind_type")],obj->query("bind_id")?obj->query("bind_id"):"��");
          msg+=sprintf(HIM+"��"+NOR+HIR+"�������ԣ� "+HIM+"                                                     ��\n"+NOR); 
          msg+=sprintf(HIM+"��"+NOR+"\t"+HIC+"��ʯ��ף�%3|d"+"/%3|d"+"\t\t"+"�� �� ֵ��%3|d"+HIM+"             ��\n"+NOR,obj->query("sockets/now"),obj->query("sockets/max"),obj->query("weapon_prop/luck"));
          if (obj->query("cold_attack"))
          {
                  msg+=sprintf(HIM+"��"+NOR+"\t"+HIC+"����������  ��    "+"\t\t��ߵȼ���%3|d"+HIM+"             ��\n"+NOR,obj->query("cold_attack/max_level"));
                  msg+=sprintf(HIM+"��"+NOR+"\t"+HIC+"��ǰ�ȼ���%3|d"+"\t\t\t�� �� ֵ��%10|d"+HIM+"      ��\n"+NOR,obj->query("weapon_prop/cold_attack"),obj->query("cold_attack/exp"));
          }
          else if(obj->query("fire_attack"))
          {
                  msg+=sprintf(HIM+"��"+NOR+"\t"+HIC+"����������  ��    "+"\t\t��ߵȼ���%3|d"+HIM+"             ��\n"+NOR,obj->query("fire_attack/max_level"));
                  msg+=sprintf(HIM+"��"+NOR+"\t"+HIC+"��ǰ�ȼ���%3|d"+"\t\t\t�� �� ֵ��%10|d"+HIM+"      ��\n"+NOR,obj->query("weapon_prop/fire_attack"),obj->query("fire_attack/exp"));
          }
          else if(obj->query("lightning_attack"))
          {
                  msg+=sprintf(HIM+"��"+NOR+"\t"+HIC+"����������  ��    "+"\t\t��ߵȼ���%3|d"+HIM+"             ��\n"+NOR,obj->query("lightning_attack/max_level"));
                  msg+=sprintf(HIM+"��"+NOR+"\t"+HIC+"��ǰ�ȼ���%3|d"+"\t\t\t�� �� ֵ��%10|d"+HIM+"      ��\n"+NOR,obj->query("weapon_prop/lightning_attack"),obj->query("lightning_attack/exp"));
          }
          else if(obj->query("poison_attack"))
          {
                  msg+=sprintf(HIM+"��"+NOR+"\t"+HIC+"����������  ��    "+"\t\t��ߵȼ���%3|d"+HIM+"             ��\n"+NOR,obj->query("poison_attack/max_level"));
                  msg+=sprintf(HIM+"��"+NOR+"\t"+HIC+"��ǰ�ȼ���%3|d"+"\t\t\t�� �� ֵ��%10|d"+HIM+"      ��\n"+NOR,obj->query("weapon_prop/poison_attack"),obj->query("poison_attack/exp"));
          }
          else if(obj->query("wind_attack"))
          {
                msg+=sprintf(HIM+"��"+NOR+"\t"+HIC+"����������  ��    "+"\t\t��ߵȼ���%3|d"+HIM+"             ��\n"+NOR,obj->query("wind_attack/max_level"));
                  msg+=sprintf(HIM+"��"+NOR+"\t"+HIC+"��ǰ�ȼ���%3|d"+"\t\t\t�� �� ֵ��%10|d"+HIM+"      ��\n"+NOR,obj->query("weapon_prop/wind_attack"),obj->query("wind_attack/exp"));
          }
      
          msg+=sprintf(HIM+"��"+NOR+HIR+"װ��Ҫ�� "+HIM+"                                                     ��\n"+NOR); 
          msg+=sprintf(HIM+"��"+NOR+"\t"+HIC+"��    �飺%14s"+"��\t"+str1+"��%4|d"+HIM+"            ��\n"+NOR,chinese_number(obj->query("weapon_wiel/exp")),j);
          msg+=sprintf(HIM+"��"+NOR+"\t"+HIC+to_chinese(obj->query("skill_type",1))+"��%5|d"+"��\t\t"+"�����Ѫ��%5|d"+HIM+"           ��\n"+NOR,obj->query("weapon_wiel/skill"),obj->query("weapon_wiel/max_qi"));   
          msg+=sprintf(HIM+repeat_string("��",34)+"\n"+NOR);
    }

    else if (obj->query("armor_prop")) 
    {
          for (i=0;i<sizeof(tianfu);i++) {
                          j=obj->query("armor_wiel/"+str[i]);
                          if (j>0) {str1=tianfu[str[i]];break;}
                  }
          msg=sprintf(HIM+"\n                   ��%22|s"+HIM+"��\n"+NOR,obj->short());
          msg+=sprintf(HIM+repeat_string("��",34)+"\n"+NOR);
          msg+=sprintf(HIM+"��"+NOR+HIR+"�������ԣ�"+HIM+"                                                      ��\n"NOR);
          msg+=sprintf(HIM+"��"+NOR+"\t"+HIC+"��    ����%10|d"+"\t\t"+"��    ֵ��%10|d"+HIM+"      ��\n"+NOR,obj->query_weight(),obj->query("value"));
          msg+=sprintf(HIM+"��"+NOR+"\t"    +HIC+"�� �� �ȣ�%7|d"+"    \t\t"+"�� �� ����%7|d"+HIM+"         ��\n"+NOR,obj->query("consistence"),obj->query("armor_prop/armor"));
          msg+=sprintf(HIM+"��"+NOR+"\t"+HIC+"�����ͣ�%-8s\t\t"+"�󶨣ɣģ�%-10s"+HIM+"      ��\n"+NOR,bind_type[obj->query("bind_type")],obj->query("bind_id")?obj->query("bind_id"):"��");
          msg+=sprintf(HIM+"��"+NOR+HIR+"�������ԣ�"+HIM+"                                                      ��\n"NOR); 
          msg+=sprintf(HIM+"��"+NOR+"\t"+HIC+"��ʯ��ף�%2|d"+"/%2|d"+"\t\t\t"+"��    �磺%3|d"+"��"+HIM+"           ��\n"+NOR,obj->query("sockets/now"),obj->query("sockets/max"),obj->query("armor_prop/wind_defence"));
          msg+=sprintf(HIM+"��"+NOR+"\t"+HIC+"��    ����%3|d"+"��\t\t\t"+"��    ��%3|d"+"��"+HIM+"           ��\n"+NOR,obj->query("armor_prop/cold_defence"),obj->query("armor_prop/fire_defence"));
          msg+=sprintf(HIM+"��"+NOR+"\t"+HIC+"��    �磺%3|d"+"��\t\t\t"+"��    ����%3|d"+"��"+HIM+"           ��\n"+NOR,obj->query("armor_prop/lightning_defence"),obj->query("armor_prop/poison_defence"));             msg+=sprintf(HIM+"��"+NOR+HIR+"װ��Ҫ�� "+HIM+"                                                     ��\n"NOR); 
          msg+=sprintf(HIM+"��"+NOR+"\t"+HIC+"��    �飺%14s"+"��\t"+str1+"��%4|d"+HIM+"            ��\n"+NOR,chinese_number(obj->query("armor_wiel/exp")),j);
          msg+=sprintf(HIM+repeat_string("��",34)+"\n"+NOR);
          
    }     
    else if (obj->query("prop"))
    {
          msg=sprintf(HIM+"\n                 ��%22|s"+HIM+"��\n"+NOR,obj->short());
          msg+=sprintf(HIM+repeat_string("��",34)+"\n"+NOR);
          msg+=sprintf(HIM+"��"+NOR+HIR+"���ԣ�"+HIM+"                                                          ��\n"NOR);
          msg+=sprintf(HIM+"��"+NOR+"\t"+HIC+"�ӹ�������������%3|d"+"��"+HIM+"                                     ��\n"+NOR,obj->query("prop/damage"));
          msg+=sprintf(HIM+"��"+NOR+"\t"+HIC+"��ħ����ħ�������ʣ�%3|d"+"��"+HIM+"                                 ��\n"+NOR,obj->query("prop/attack"));
          msg+=sprintf(HIM+"��"+NOR+"\t"+HIC+"�����ˣ����뱦ʯ�������ʣ�%3|d"+"��"+HIM+"                           ��\n"+NOR,obj->query("prop/luck"));
          msg+=sprintf(HIM+repeat_string("��",34)+"\n"+NOR);
    }

   
   inv = all_inventory(obj);
   if( sizeof(inv) ) {
     inv = map_array(inv, "inventory_look", this_object() );
     message("vision", sprintf("�����У�\n  %s\n",
        implode(inv, "\n  ") ), me);
   }
   if(me->query("ll")) me->set_temp("ll",msg);
   tell_object(me,msg);
   return 1;
}



string inventory_look(object obj, int flag)
{
   string str;

   str = obj->short();
   if( obj->query("equipped") )
     str = HIC "  ��" NOR + str;
   else if( !flag )
     str = "    " + str;
   else
     return 0;

   return str;
}



int help (object me)
{
   write(@HELP
 ָ���ʽ: ll [<��Ʒ>|in <����>
 
���ָ������鿴ĳ��������Ʒ�����ԣ���ʦ���Բ鿴�������ϵ���Ʒ��
 
HELP
);
   return 1;
}


