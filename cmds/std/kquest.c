inherit F_CLEAN_UP;
int time_period(int timep, object me);
int main(object ob, string arg)
{
        object me;
        int turn;
        string str="��ǰ����ս����\n",name="��";
        if (!wizardp(ob) || arg == "") me = ob;
        else
        {
        if( arg ){
        me = present(arg, environment(ob));
        if (!me) me =  find_player(arg);
        if (!me) return notify_fail("��Ҫ�쿴˭������\n");
                        }
                        else
                                me = ob;
        }
        if (me!=ob) name=me->query("name");
        if(!me->query("mieyao")&&!me->query("mpmieyao"))
               return notify_fail(name+"����û����ս����\n");
        str=name+str;
        if (name = me->query("mieyao/name"))
           {
           turn=me->query_temp("mieyao/level")+1;
           str+="��ս��ʹ����"+chinese_number(turn)+"����ս����"+ name +"��";
           if (!me->query("mieyao/done"))
                 str+="û����ɡ�\n";
           else
                 str+="�Ѿ���ɡ�\n";
           }

        write(str);
        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : kquest
 
���ָ�������ʾ���㵱ǰ����������

HELP
        );
        return 1;
}

