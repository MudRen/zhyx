// wear.c

#include <ansi.h>

inherit F_CLEAN_UP;

int do_wear(object me, object ob);

int main(object me, string arg)
{
        object ob, *inv;
        int i, count;

        if( !arg ) return notify_fail("��Ҫ����ʲô��\n");
        
        if ( time() - me->query_temp("last_time/remove") < 5 )
                  return notify_fail("��ʲô����������\n");     
        
        if(arg=="all") {
                inv = all_inventory(me);
                for(count=0, i=0; i<sizeof(inv); i++) {
                        if( inv[i]->query("equipped") ) continue;
                        if(do_wear(me, inv[i]) ) count ++;
                }
                write("Ok.\n");
                return 1;
        }

        if( !objectp(ob = present(arg, me)) )
                return notify_fail("������û������������\n");
                        
        if( ob->query("equipped") )
                return notify_fail("���Ѿ�װ�����ˡ�\n");

        return do_wear(me, ob);
}

int do_wear(object me, object ob)
{
        string str;

        if( ob->query("owner_id") && ob->query("owner_id") != getuid(me) )   {
                destruct(ob);
                return notify_fail("�´α���͵���˵Ķ�����\n");
        }

        if( ob->query("No_Wear") )
                return notify_fail("����·������ٴ��ˣ�\n");
                
        if ( time() - me->query_temp("last_time/remove") < 6 )
                  return notify_fail("��ʲô����������\n");

        if( ob->query("female_only")
        &&      (string)me->query("gender") != "Ů��" )
                return notify_fail("����Ů�˵���������һ��������Ҳ�봩����Ҳ���ߣ�\n");

        if( ob->query("male_only")
        &&      (string)me->query("gender") != "����" )
                return notify_fail("���Ǵ����˵��·�����һ������ҾͲ�Ҫ�����ˣ�\n");
  
   //add by wsw 20051010
  //����װ������������
  if (ob->query("changed") && (!ob->query("primitive_id") ||!ob->query("unique_code") ) && !wizardp(me)) 
  	return notify_fail("���װ����������������ʹ�ã�\n");
  if (ob->query("bind_id") && ob->query("bind_id") != getuid(me) ) 
  	return notify_fail("�ⲻ�������Ʒ��\n");
   
   //����װ���������� wsw��2003��11��
  if (!wizardp(me)) {
    if( ob->query("armor_wiel/exp")*1000> me->query("daoxing")&& !wizardp(me) )  return notify_fail("��ĵ��в���������ll����鿴װ��Ҫ��\n");
    if( ob->query("armor_wiel/str")> me->query("str") )  return notify_fail("����츳����������ll����鿴װ��Ҫ��\n");
    if( ob->query("armor_wiel/con")> me->query("con") )  return notify_fail("����츳����������ll����鿴װ��Ҫ��\n");
    if( ob->query("armor_wiel/int")> me->query("int") )  return notify_fail("����츳����������ll����鿴װ��Ҫ��\n");
    if( ob->query("armor_wiel/per")> me->query("per") )  return notify_fail("����츳����������ll����鿴װ��Ҫ��\n");
    if( ob->query("armor_wiel/cps")> me->query("cps") )  return notify_fail("����츳����������ll����鿴װ��Ҫ��\n");
    if( ob->query("armor_wiel/spi")> me->query("spi") )  return notify_fail("����츳����������ll����鿴װ��Ҫ��\n");
    if( ob->query("armor_wiel/cor")> me->query("cor") )  return notify_fail("����츳����������ll����鿴װ��Ҫ��\n");
    if( ob->query("armor_wiel/kar")> me->query("kar") )  return notify_fail("����츳����������ll����鿴װ��Ҫ��\n");
  }
        if( ob->wear() ) {
        	    if (ob->query("bind_type") >=1 && !ob->query("bind_id"))  ob->set("bind_id",getuid(me));//add by wsw 20051011
                if( !stringp(str = ob->query("wear_msg")) )
                        switch( ob->query("armor_type") ) {
                                case "cloth":
                                case "armor":
                                case "boots":
                                case "surcoat":
                                        str = YEL "$N����һ" + ob->query("unit") + "$n��\n" NOR;
                                        break;
                                case "head":
                                case "neck":
                                case "wrists":
                                case "finger":
                                case "hands":
                                        str = YEL "$N����һ" + ob->query("unit") + "$n��\n" NOR;
                                        break;
                                case "waist":
                                        str = YEL "$N����һ" + ob->query("unit") + ob->query("name") + "��\n" NOR;
                                        break;
                                default:
                                        str = YEL "$Nװ��$n��\n" NOR;
                        }
                message_vision(str, me, ob);
                me->set_temp("last_time/wear",time());
                return 1;
        } else
                return 0;
}

int help(object me)
{
        write(@HELP
ָ���ʽ��wear|chuan <װ������>
 
���ָ������װ��ĳ�����ߡ�
 
HELP
    );
    return 1;
}

