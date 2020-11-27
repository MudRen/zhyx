// shewu.c ����
#include <ansi.h>
#include <skill.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me)
{
    int skill,n;
    object ob,snake;
    me=this_player();
    skill = me->query_skill("xiyu-tiezheng",1);

    if ((int)me->query("neili") < 500 )
        return notify_fail("���������������,�޷����������衹��\n");
    
    if ((int)me->query("jingli") < 50 )
        return notify_fail("��ľ�������,�޷�ר�ĵ��١�\n");

    if (me->query_skill("guzheng-jifa",1)<100)
        return notify_fail("��Ĺ��ݼ���������\n");
    
    if (skill < 100)
        return notify_fail("��ļҴ�����������졣\n");

    if (! objectp(ob = me->query_temp("handing")) || ! ob->valid_as_zheng()) 
        return notify_fail("�㲻�ó���������ô���ࣿ\n"); 

    if(!environment(me)->query("can_perform_shewu"))  
        return notify_fail("�����ﵯ���ƺ���̫�ʺϰɡ�\n"); 

    if(me->is_busy())
        return notify_fail("��������æ���أ�\n");


    message_vision(HIB"$N��ϥ������˫�ַ��٣�ʱ���켲��ʱ�����������ƺ���δ����������\n"NOR,me); 
    
    if(skill >= 100 && skill <= 150)  n =10; 
    else if(skill > 150 && skill <= 200) n = 8;
    else if(skill > 200 && skill <= 250) n = 6;
    else if(skill > 250 && skill <= 300) n = 4;
    else if(skill > 300) n = 2;  
    if (random(n)==1 )
    {
        switch(random(4))
        {
            case 0:
            message_vision("ͻȻ��$N�о���ߺ�Ӱ������ֻ��һ���������������ӣ���������$N˫�ֵĽ����趯��\n",me); 
            snake=new("/clone/beast/dushe");
            snake->move(environment(me));
            break;
        
            case 1:
            message_vision("ͻȻ��$N�о���ߺ�Ӱ������ֻ��һ���������������ӣ���������$N˫�ֵĽ����趯��\n",me);
            snake=new("/clone/beast/jinshe");
            snake->move(environment(me));
            break;
        
            case 2:
            message_vision("ͻȻ��$N�о���ߺ�Ӱ������ֻ��һ���岽�����������ӣ���������$N˫�ֵĽ����趯��\n",me);
            snake=new("/clone/beast/wubushe");        
            snake->move(environment(me));
            break;
        
            case 3:
            message_vision("ͻȻ��$N�о���ߺ�Ӱ������ֻ��һ����Ҷ�������������ӣ���������$N˫�ֵĽ����趯��\n",me);
            snake=new("/clone/beast/qingshe");        
            snake->move(environment(me));
            break;
        }
        me->add("neili",-100); 
        me->add("jingli",-200); 
        me->start_busy(5);
    }
    else
    {
        message_vision(GRN"$N�������ӣ�����һ����Ѫ����ӿ���չ�վ��������\n"NOR,me);
        me->add("neili",-100); 
        me->add("jingli",-50); 
        me->start_busy(3);
    }
    return 1;    
}
