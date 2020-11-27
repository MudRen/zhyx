// wield.c

inherit F_CLEAN_UP;

int do_wield(object me, object ob);

int main(object me, string arg)
{
        object ob, *inv;
        int i, count;

        if( !arg ) return notify_fail("��Ҫװ��ʲô������\n");

        if(arg=="all") {
                inv = all_inventory(me);
                for(count=0, i=0; i<sizeof(inv); i++) {
                        if( inv[i]->query("equipped") ) continue;
                        if(do_wield(me, inv[i]) ) count ++;
                }
                write("Ok.\n");
                return 1;
        }

        if( !objectp(ob = present(arg, me)) )
                return notify_fail("������û������������\n");

        if( ob->query("equipped") )
                return notify_fail("���Ѿ�װ�����ˡ�\n");

        return do_wield(me, ob);
}

int do_wield(object me, object ob)
{
        string str;

    if( ob->query("owner_id") && ob->query("owner_id") != getuid(me) )   {
                destruct(ob);
                return notify_fail("�´α���͵���˵Ķ�����\n");
        }
        
        if( me->query_temp("No_Wield") )
                return notify_fail("��ԭ�����֣������ٳֱ�����\n");
  //add by wsw 20051010
  //����װ������������
  if (ob->query("changed") && (!ob->query("primitive_id") ||!ob->query("unique_code") ) && !wizardp(me)) 
  	return notify_fail("���װ����������������ʹ�ã�\n");
  if (ob->query("bind_id") && ob->query("bind_id") != getuid(me) ) 
  	return notify_fail("�ⲻ����ı�����\n");
  
                
  //����װ���������� wsw��2003��11��
    if(ob->query("durability/max")>0 && ob->query("durability/now")<=0)
        return notify_fail("���������ʱ�������ˡ�\n");
if (!wizardp(me)) {
    if( ob->query("weapon_wiel/exp")*1000> me->query("daoxing") )  return notify_fail("��ĵ��в���������ll����鿴װ��Ҫ��\n");
    if( ob->query("weapon_wiel/str")> me->query("str") )  return notify_fail("����츳����������ll����鿴װ��Ҫ��\n");
    if( ob->query("weapon_wiel/con")> me->query("con") )  return notify_fail("����츳����������ll����鿴װ��Ҫ��\n");
    if( ob->query("weapon_wiel/int")> me->query("int") )  return notify_fail("����츳����������ll����鿴װ��Ҫ��\n");
    if( ob->query("weapon_wiel/per")> me->query("per") )  return notify_fail("����츳����������ll����鿴װ��Ҫ��\n");
    if( ob->query("weapon_wiel/cps")> me->query("cps") )  return notify_fail("����츳����������ll����鿴װ��Ҫ��\n");
    if( ob->query("weapon_wiel/spi")> me->query("spi") )  return notify_fail("����츳����������ll����鿴װ��Ҫ��\n");
    if( ob->query("weapon_wiel/cor")> me->query("cor") )  return notify_fail("����츳����������ll����鿴װ��Ҫ��\n");
    if( ob->query("weapon_wiel/kar")> me->query("kar") )  return notify_fail("����츳����������ll����鿴װ��Ҫ��\n");
    if( ob->query("weapon_wiel/max_kee")> me->query("max_kee") )  return notify_fail("��������Ѫ����������ll����鿴װ��Ҫ��\n");
    if( ob->query("weapon_wiel/max_sen")> me->query("max_sen") )  return notify_fail("��ľ��񲻹�������ll����鿴װ��Ҫ��\n");
    if( ob->query("weapon_wiel/skill")> me->query_skill(ob->query("skill_type"),1) )  return notify_fail("��ļ��ܲ�����\n");
}               

        if( ob->wield() ) {
        	if (ob->query("bind_type") >=1 && !ob->query("bind_id"))  ob->set("bind_id",getuid(me));//add by wsw 20051011
                if( !stringp(str = ob->query("wield_msg")) )
                        str = "$Nװ��$n��������\n";
                message_vision(str, me, ob);
                return 1;
        } else
                return 0;
}

int help(object me)
{
        write(@HELP
ָ���ʽ��wield|zhuangbei <װ������>
 
���ָ������װ��ĳ����Ʒ������, �����Ҫӵ��������Ʒ.
 
HELP
    );
    return 1;
}

