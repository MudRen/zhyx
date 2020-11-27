// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit F_CLEAN_UP;
int check_item(string item);

int main(object me, string arg)
{
        object ob;
        string name, item, zhiwei, id, n1, n2;
        string banghui;
        int lvl, flag;
        
        if (! (banghui = me->query("bunch/bunch_name")))
              return notify_fail("��û�вμ��κΰ�ᣬ�޷���������ְλ��\n");
        
        flag = 0;
        
        if (me->query("bunch/level") == 9   
        ||  (intp(me->query("bunch/level")) 
        &&  (int)me->query("bunch/level") > 2))
                flag = 1;               
        
        if (! arg)   
                return notify_fail("ָ���ʽ��renming <ĳ��> <ְ��>��renming <ĳ��> <����> <ְ��>\n");
                
        if (! flag)
                return notify_fail("���ڰ���ְλ̫�ͣ���Ȩ��������ְλ��\n");
                
        if (sscanf(arg, "%s %s %s", id, item, zhiwei) == 3) 
        {
                ob = present(id, environment(me));
                
                if (! ob) return notify_fail("���û����ô���ˡ�\n");
                
                if (! ob->is_character())
                        return notify_fail("��������ǲ������ˣ�\n");
                                
                if (! playerp(ob))  
                        return notify_fail("��ֻ�Ա��������ʹ���������\n");
                        
                if (banghui != (string)ob->query("bunch/bunch_name"))
                        return notify_fail("��ֻ�Ա��������ʹ���������\n");
                        
                if ((int)me->query("bunch/level") < (int)ob->query("bunch/level"))
                        return notify_fail("�Է��ڰ��е�ְλ����ߣ�������������Ц��\n");
                        
                if (me->is_busy() || me->is_fighting())
                        return notify_fail("����æ���أ�\n");
                        
                if (ob->is_busy() || ob->is_fighting())
                        return notify_fail("�Է���æ���أ�\n");
                        
                if (ob == me)
                        return notify_fail("�Լ������Լ���\n");
                        
                if (! check_item(item))
                        return notify_fail("��������ְ����������ģ���Ϊ�������֣�\n");
                        
                if (zhiwei != "����" && zhiwei != "����" && zhiwei != "̳��" 
                &&  zhiwei != "����" && zhiwei != "����" && zhiwei != "����"
                &&  zhiwei != "����")
                        return notify_fail("������ְλ���϶���Ϊ������,����,̳��,����,����,����,���ڡ�\n");
                        
                switch (zhiwei)
                { 
                case "������": 
                        lvl = 6;
                        break;
                case "����":
                        lvl = 5;
                        break;
                case "����":
                        lvl = 4;
                        break;
                case "����":
                case "̳��":
                case "����":
                case "����":
                        lvl = 3;
                        break;
                case "����":
                        lvl = 2;
                        break;
                case "����":
                        lvl = 1;
                        break;
                }
                
                if ((int)me->query("bunch/level") <= lvl)
                        return notify_fail("��ְλ̫�ͣ���Ȩ�����������ְλ��\n");
                        
                else 
                {
                        ob->set("bunch/title", item + zhiwei);
                        ob->set("bunch/level", lvl);
                        message_vision("$N����$nΪ��" + banghui + "��" + item + zhiwei + "��\n", me, ob);
                        return 1;
                }
        }
     
               
        if (sscanf(arg, "%s %s", id, name) == 2) 
        {
                ob = present(id, environment(me));
                
                if (! ob) return notify_fail("���û����ô���ˡ�\n");
                
                if (! ob->is_character())
                        return notify_fail("��������ǲ������ˣ�\n");
                        
                if (!userp(ob)) return notify_fail("��ֻ�Ա��������ʹ���������\n");
                
                if (banghui != (string)ob->query("bunch/bunch_name"))
                        return notify_fail("��ֻ�Ա��������ʹ���������\n");
                        
                if ((int)me->query("bunch/level") <= (int)ob->query("bunch/level"))
                        return notify_fail("�Է��ڰ��е�ְλ����ߣ�������������Ц��\n");
                        
                if (me->is_busy() || me->is_fighting())
                        return notify_fail("����æ���أ�\n");
                        
                if (ob->is_busy() || ob->is_fighting())
                        return notify_fail("�Է���æ���أ�\n");
                        
                if (ob == me)
                        return notify_fail("�Լ������Լ���\n");
                        
                if (name != "������" && name != "����" && name != "����" && name != "����"
                &&  name != "̳��" && name != "����" && name != "����" && name != "����"
                &&  name != "����")
                        return notify_fail("������ְλ���϶���Ϊ��������������, ����, ����, ̳��, ����, ����, ����, ���� ��\n");
                        
                switch (name)
                { 
                case "������": 
                        lvl = 6;
                        break;
                case "����":
                        lvl = 5;
                        break;
                case "����":
                        lvl = 4;
                        break;
                case "����":
                case "̳��":
                case "����":
                case "����":
                        lvl = 3;
                        break;
                case "����":
                        lvl = 2;
                        break;
                case "����":
                        lvl = 1;
                        break;
                }
                
                if ((int)me->query("bunch/level") <= lvl)
                        return notify_fail("��ְλ̫�ͣ���Ȩ�����������ְλ��\n");
                        
                else 
                {
                        ob->set("bunch/title", name);
                        ob->set("bunch/level", lvl);
                        message_vision("$N����$nΪ��" + banghui + "��" + name + "��\n", me, ob);
                        return 1;
                }
       }
       else     return notify_fail("ָ���ʽ��renming <ĳ��> <ְ��>��renming <ĳ��> <����> <ְ��>\n");
}

int check_item(string item)
{
        int i;

        i = strlen(item);

        if( (strlen(item) < 4) || (strlen(item) > 16 ) ) {
                return 0;
        }
        while(i--) {
                if( item[i]<=' ' ) {
                        return 0;
                }
        if( i%2==0 && !is_chinese(item[i..<0]) ) {
                        return 0;
        }
        }
        return 1;
}

int help(object me)
{
        write(@HELP

ָ���ʽ��renming <ĳ��> <ְ��> �� renming <ĳ��> <����> <ְ��>

����ָ������Ұ���о���һ����λ���˶������õ��������Ϊ�����
����Ұ��ڷ�����ְ����̳�������������������˵ȳ�ν��

HELP
        );
        return 1;
}


