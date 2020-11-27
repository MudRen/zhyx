// mingsi.c

#include <skill.h>

inherit F_CLEAN_UP;

int mingsi(object me);
int halt_mingsi(object me);

void create() { seteuid(getuid()); }

int main(object me)
{	
	object where;        

	seteuid(getuid());
	where = environment(me);

       if ( ! me->query("special_skill/lonely") ) return 0;
 
	if (me->is_busy() || me->query_temp("pending/mingsi") 
           ||  me->query("doing") )
		return notify_fail("��������æ���ء�\n");

	if (where->query("pigging"))
		return notify_fail("�㻹��ר�Ĺ���ɣ�\n");

	if (me->is_fighting())
		return notify_fail("ս���л��Ǻúõ�����Եаɡ�\n");

      if (where->is_chat_room())
              return notify_fail("�㲻��������������ڤ˼��\n");	

	if ((int)me->query("jing") * 100 / (int)me->query("max_jing") < 80)
		return notify_fail("�����ھ�����֧���޷�ڤ˼��\n");

	if ((int)me->query("qi") * 100 / (int)me->query("max_qi") < 80)
		return notify_fail("������������֧���޷�ڤ˼��\n");

	me->set_temp("pending/mingsi", 1);    
       me->set_temp("mingsi/time",  10 + random(5) );
   
       me->set_short_desc("��������ڤ˼��");

	message_vision("$N�����Ŀ�����ȴ�������ʼڤ˼��\n", me);

	me->start_busy(bind((:call_other, __FILE__, "mingsi" :), me),
                       bind((:call_other, __FILE__, "halt_mingsi" :), me));
       return 1;
}

int mingsi(object me)
{
        
    if ( me->query_temp("mingsi/time") > 0 )
    {
       if ( me->query("potential") <= me->query_potential_limit() ) 
           me->add("potential", 7 + random(8));

       if ( me->query("experience") <= me->query_experience_limit() )
           me->add("experience", ( 7 + random(8) ) / 2 + random (2));

   
           me->add("combat_exp",  10 + random(5));
     
       me->add_temp("mingsi/time", -1);       
       return 1;
    }
       me->delete_temp("mingsi");
	me->delete_temp("pending/mingsi");
       me->set_short_desc(0);

    if ( me->query("potential") >= me->query_potential_limit() ) 

       write("��ڤ˼��ϣ��е��Լ���Ǳ���ƺ��Ѿ��ﵽ�����ޡ�\n");
    else 
    if ( me->query("experience") >= me->query_experience_limit() )

       write("��ڤ˼��ϣ��е��Լ���ʵս����ƺ��Ѿ��ﵽ�����ޡ�\n");
    else
       write("��ڤ˼��ϣ��о�������ˬ���ƺ�Ǳ�ܺ�ʵս��ᶼ���˽�����\n");

       message("vision", me->name() + "��������˫�ۣ����������ڤ˼��\n",
                        environment(me), ({ me }));	
}

int halt_mingsi(object me)
{
        tell_object(me, "���Ȼ�ع���������������ڤ˼��\n");
        tell_room(environment(me), me->name() + "��Ȼ����˫�ۣ�ֹͣ��ڤ˼��\n", me);
	 me->delete_temp("pending/mingsi");
        me->delete_temp("mingsi");
        me->set_short_desc(0);
	 return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : mingsi

��ɷ����ʹ�����ָ�����Ѹ�ٵ�����Ǳ�ܺ�ʵս��ᡣ

HELP );
        return 1;
}
