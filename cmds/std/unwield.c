// unwield.c

inherit F_CLEAN_UP;

int do_unwield(object me,object ob);
int main(object me, string arg)
{
	object ob, *inv;
	string str;
	int i,count;

	if( !arg ) return notify_fail("��Ҫ�ѵ�ʲô��\n");
	if(arg=="all") {
		inv = all_inventory(me);
		for(count=0, i=0; i<sizeof(inv); i++) 
		{
			if( ! inv[i]->query("equipped") ) continue;
			if(do_unwield(me, inv[i])==1 ) 
			{
				break;
			}
				count ++;
		}
		write("���ˡ�\n");
		return 1;
	}

	if( !objectp(ob = present(arg, me)) )
		return notify_fail("������û������������\n");

	if( (string)ob->query("equipped")!="wielded" )
		return notify_fail("�㲢û��װ������������Ϊ������\n");
	return do_unwield(me,ob);
}

int do_unwield(object me,object ob)
{
	string str;
	if ((string)ob->query("equipped")=="wielded") 
	if( ob->unequip() ) 
	{
		if( !stringp(str = ob->query("unwield_msg")))
			str = "$N�������е�$n��\n";
		message_vision(str, me, ob);
		return 1;
	}
}
int help(object me)
{
  write(@HELP
ָ���ʽ : unwield <��Ʒ��>
 
���ָ������������е�������
 
HELP
    );
    return 1;
}
 
