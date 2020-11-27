//Edit By gladiator

#define TEACH_DIR       "/u/gladiator/employ_teacher"
#define TEACH_FILENAME  "teach.s"

#include <ansi.h>

inherit F_CLEAN_UP;
inherit F_SAVE;

mapping *notes;

string query_save_file()
{
        return TEACH_DIR + TEACH_FILENAME ;
}

void done_post(object me, mapping note, string text)
{
    int i;
    note["msg"] = text;
    
    i = sizeof(notes);
    for( ; i > 0; i-- ) 
        if( notes[i-1]["author"] == me->query("id") ) break;
    
    if( !pointerp(notes) || i > 0 )
        if(!sizeof(notes)) notes = ({ note });
        else {
            notes[i-1]["title"] = note["title"];
            notes[i-1]["author"] = note["author"];
            notes[i-1]["msg"] = note["msg"];
            notes[i-1]["time"] = note["time"];
            notes[i-1]["solve"] = "";
             }
        else
            notes += ({ note });
            tell_object(me, HIY "���������Ϣ������ϡ������Ϣ�Ѿ����ӵ����ֵ�ʦ֪ͨ�����\n");
            tell_object(me, HIY "���ֵ�ʦ���ڴ���������ң���ȴ���\n");
            tell_object(me, HIY "�������æ���Լ������飬��һ��ʱ��������teach read�鿴"
                                "�Ƿ�������ظ���\n" NOR);
        save();
    return;
}

void list_bug(object me)
{
    int i;
    string str,s;
    if (sizeof(notes)<1) {
        write("û�����ַ��������Ϣ��\n");
        return;
    } 
    s = sprintf("���ַ���������б�����:\n"
                "----------------------------------------------------------------------\n");
    for( i = 0; i<sizeof(notes); i++){
        str = sprintf("%d) %-50s %10s %s \n",
                           i+1, notes[i]["title"], notes[i]["solve"]==""?"No solved":"By "+notes[i]["solve"],
                           ctime(notes[i]["time"])[0..9] );
        s = s + str;
    }
    me->start_more(s);                
}

void do_read(object me, int i) 
{
    string s;
    if( i > sizeof(notes) || i < 1) {
        write("�޴˱��!!\n");
        return;
    }
    s = sprintf("%d) %-50s %10s %s\n"
              "----------------------------------------------------------------------\n"
              "%s",
               i, notes[i-1]["title"], notes[i-1]["solve"]==""?"No solved":"By "+notes[i-1]["solve"],
               ctime(notes[i-1]["time"])[0..9], notes[i-1]["msg"] );
    me->start_more(s);
}

int search_id(string id)
{
    int i;
    if( !(i = sizeof(notes)) ) return 0;
    for( ; i > 0; i-- ) 
        if( notes[i-1]["author"] == id ) break;
    return i;
}

int do_solve(object me, int i)
{
    if( i > sizeof(notes) || i < 1) {
        write("�޴˱��!!\n");
        return 0;
    } 
    if ( notes[i-1]["solve"]!="" ) {
        write(notes[i-1]["solve"]+"�Ѿ���־��!\n");
        return 1;
    }
    notes[i-1]["solve"] = me->query("id");
    save();
    write("�������Ϣ�ѱ�־Ϊ�����\n");
    return 1;
}

int main(object me, string arg)
{
    mapping note;
    object where;
    string s, str,arg1; 
    int i, arg2;
    restore();
    
    if (!arg) {
        if(!wiz_level(me))
        {
            tell_object(me, HIY "������" HIY MUD_NAME HIY "�������������ͣ�ͻȻ���ֲ�֪������ôŪ�ˡ�\n" NOR);
            tell_object(me, HIY "��Ͻ������ֵ�ʦ������������źţ�HELP������\n" NOR);
            where = environment(me);
            if (!where) 
                s=sprintf("%s(%s)���",
                        (string)me-> name(),
                        (string)me-> query("id"));
            else
                s=sprintf("%s(%s)��%s(%s)���",
                        (string)me->name(),
                        (string)me->query("id"),
                        (string)where ->query("short"),
                        (string)file_name(where));
            note = allocate_mapping(5);
            note["title"] = s;
            note["author"] = me->query("id"); 
            note["time"] = time();
            note["solve"] = "";
            me->edit( (: done_post, me, note :) );
        }
        else {
            list_bug(me);
        }
        return 1;
    } 

    if( sscanf(arg, "%s %s", s, arg1) == 2 ) {
        if( !wiz_level(me) || !me->query("employ/job")) return notify_fail("���޴�Ȩ�ޣ�����ʹ�÷�������� help teach \n");
        if ( s != "solve" ) return notify_fail("��ʽ���ԣ�����ʹ�÷�������� help teach \n");
        if ( arg1 == "all" ) {
           if( !(i = sizeof(notes)) ) return notify_fail("û�˷��������Ϣ��\n");
           for( ; i > 0; i-- ) 
               notes[i-1]["solve"] = me->query("id");
           write("���е������Ϣ�Ѿ�����ˡ�\n");
           return 1;
        }
        i = search_id(arg1);
        if( i > 0 ) { 
            do_solve( me, i );
            return 1;
        }
    }
    if( sscanf(arg, "%s %d", s, arg2) == 2 ) {
        if( !wiz_level(me) || !me->query("employ/job")) return notify_fail("���޴�Ȩ�ޣ�����ʹ�÷�������� help teach \n");
        if ( s != "solve" || !me->query("employ/jon")) return notify_fail("���޴�Ȩ�ޣ�����ʹ�÷�������� help teach \n");
        do_solve( me, arg2 ); 
        return 1;
    }
    if ( sscanf(arg, "%s", s) == 1 ) 
    switch(arg){
        case "read":       
            if( !(i = sizeof(notes)) )
                return notify_fail("��û���˷��������Ϣ��\n");
            else {
                i = search_id( me->query("id") );
                do_read(me,i);
            }
            break;
        case "list":
            if( !wiz_level(me) || !me->query("employ/job") ) return notify_fail("��ʽ���ԣ�����ʹ�÷�������� help teach \n");
            list_bug(me);
            break;
        case "pack":
            if( !wiz_level(me) ) return notify_fail("����Ȩɾ�������Ϣ������ʹ�÷�������� help teach \n");
            if( !(i = sizeof(notes)) ) return notify_fail("û���˷��������Ϣ��\n");
            for( ; i > 0; i-- ) 
                if( "" != notes[i-1]["solve"] ) {
                    printf("%s�������Ϣ�Ѿ���ɾ���ˣ�\n", notes[i-1]["author"]);
                    if( sizeof(notes) == 1 ) notes = ({});
                    else if(i==1) notes = notes[1..sizeof(notes)-1];
                    else if( i == sizeof(notes) ) notes = notes[0..sizeof(notes)-2];
                    else notes = notes = notes[0..i-2] + notes[i..sizeof(notes)-1];
                }
            save();
            break;
        case "solve":
            if( !wiz_level(me) || !me->query("employ/job") ) return notify_fail("���޴�Ȩ�ޣ�����ʹ�÷�������� help teach \n");
            return notify_fail("��ʽ: teach solve <��Ż����id>\n");
            break;
        default:
            if( !wiz_level(me) ) return notify_fail("��ʽ���ԣ�����ʹ�÷�������� help teach \n");
            if( sscanf(arg, "%d", i) == 1 )
                do_read( me, i );
            else if( sscanf( arg, "%s", str ) == 1 ) {
                i = search_id(str);
                if( i == 0 ) return notify_fail("�޴���ҷ����������Ϣ��\n");
                do_read( me, i );
            }
    }
    else return notify_fail("��ʽ���ԣ�����ʹ�÷�������� help teach \n");
    return 1;
}

int help(object me)
{
        if (!wiz_level(me) )
        write(@HELP
ָ���ʽ : 
           teach
           teach read
���ָ����������������ֵ�ʦ������
����������ϵͳ����ʾ������������ݵ����������������Ӧ�ý�
���ֵ��������Ҫ��̵�����˵������Ա������ֵ�ʦ���������
ÿ�����ֻ����һ�������Ϣ���µ������Ϣ��������ǰ�����롣
������ teach read �Ķ��Լ������������Ϣ��
HELP
    );
        else 
write(@HELP
ָ���ʽ : 
           teach
           teach <��������id>
           teach list
           teach pack
           teach solve <��������id>
���ָ����Ը������ֵ�ʦ��������������̡�teach �� teach list �Ĺ���һ����
���ǽ����е������Ϣ�����б���������teach������ݲ����Ĳ�ͬ������ʾ
��Ӧ������Ӧ�����̵���ϸ��Ϣ��teach solve������־ĳ�������Ϣ�Ѿ�������ˡ�
teach pack ��ɾ�������Ѿ���־Ϊ����˵������Ϣ��
HELP
    );
    return 1;
}

