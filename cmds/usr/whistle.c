
#include <ansi.h>
inherit F_CLEAN_UP;
#define DEATH_PERIOD 1200
int main(object me, string arg)
{
	object pet;
	object *ob_list;
	int i;
	string id,name;
	string file;
	if(me->query("jing")<50) return notify_fail("�㾫��������\n");
	if(me->is_busy()) return notify_fail("�����ڲ����Դ����ڡ�\n");
 if(me->query_temp("is_riding"))  return notify_fail("�������������ϲ����Դ����ڡ�\n");
	if(me->is_ghost()) return notify_fail("��겻���Դ����ڡ�\n");
	if(!me->query("marks/pet")) return notify_fail("��û���Լ��ĳ��\n");
              write("����˷ܵ��ڵ��¹���һȦ�������ش�����Ư���Ŀ��ڣ�����\n"); 
//	if(environment(me)->query("NONPC")) return 1;
	file = me->query_save_file();
	file += ".pet.o";
	ob_list = children("/clone/pet/pet");
	for(i=0; i<sizeof(ob_list); i++) 
		if(ob_list[i]->query("possessed") == me)
			pet = ob_list[i];
	if(!pet && file_size(file) > 0 )
	{
		seteuid(getuid());
		pet = new("/clone/pet/pet");
		pet->set("owner",me->query("id"));
		pet->restore();
		id = pet->query("id");
		name = pet->query("name");
		pet->set("id",id);
		pet->set_name(name,({id}));
		pet->set("possessed",me);
		pet->setup();

	}
	me->add("jing",-50);
	if(pet && environment(pet) != environment(me) 
	&& time() - (int)pet->query("deathstamp") > 1200
	&& !pet->is_fighting())
	{
	pet->move(environment(me));
	pet->reset_action();
	pet->set_temp("owner",me);
        pet->set("ownmake",1);
        pet->set("no_drop",1);
	pet->set_temp("ownername",me->query("name"));
	pet->delele("is_rided_by");
      message_vision("$nֻ�����Դ�������һ�£�һ��ͷ����$N�Ѿ����Լ���ǰ��\n",pet,me);    
// let pet be our protector
	if(me->is_fighting())
	{
	object *enemy;
	enemy = me->query_enemy();
        i = sizeof(enemy);
        while(i--) {
                if( enemy[i] && living(enemy[i]) ) {
                        pet->kill_ob(enemy[i]);
                        if( userp(enemy[i]) ) enemy[i]->fight_ob(pet);
                        else enemy[i]->kill_ob(pet);
						    }
		    }
//        me->remove_all_killer();
	}
	
	pet->set_leader(me);
	}
	else
		if (pet) 
	{pet->save();
          message_vision("ֻ����$N��������Ҷ㣬�Ҷ㣬�Ҷ��㣬��������Ӳ����ˡ�\n",pet);
   pet->delele_temp("is_rided_by");
	me->delete_temp("is_riding");
	destruct(pet);
	}
	return 1;
}
int help(object me)
{
        write(@HELP
ָ���ʽ : whistle

����뿴�����ļ��еġ�����ƪ��
HELP
        );
        return 1;
}
