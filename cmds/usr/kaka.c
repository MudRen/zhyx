inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob, *inv;
	int i, count;
           string str;


	if( !arg ) return notify_fail("��Ҫ�鿴ʲô������\n");
   
	
	if( !objectp(ob = present(arg, me)) )
		return notify_fail("������û������������\n"); 

       if (ob->query("weapon_prop/damage"))
             message("vision", ob->short()+ "���˺�ֵΪ"+ob->query("weapon_prop/damage")+"\n",me);
       else 
             message("vision", ob->short()+ "���˺�ֵΪ"+ob->query("armor_prop/unarmed_damage")+"\n",me);
     return 1;
	}


