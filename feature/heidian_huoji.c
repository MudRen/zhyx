//�ڵ��Ƴ���
//edit by smallfish

#include <dbase.h>

//�޸Ļ������
int do_modify(string arg)
{
        string msg;
        msg = HEIDIAN_D->do_modify(this_object(),this_player(),arg);
        write(msg);
        return 1;
}

//��ۻ���
int do_stock(string arg)
{
        string msg;
        msg = HEIDIAN_D->do_stock(this_object(),this_player(),arg);
        write(msg);
        return 1;
}

//ȡ�»���
int do_unstock(string arg)
{
       string msg;
       msg = HEIDIAN_D->do_unstock(this_object(),this_player(),arg);
       write(msg);
       return 1;
}

//��ѯ�����б�
int do_list(string arg)
{
        string msg;
        msg = HEIDIAN_D->do_list(this_object(),this_player(),arg);
        write(msg);
        return 1;
}

//�������
int do_buy(string arg)
{
        return HEIDIAN_D->do_buy(this_object(),this_player(),arg);
}

//��������
int do_jiezhang()
{
        string msg;
        msg = HEIDIAN_D->do_jiezhang(this_object(),this_player());
        write(msg);
        return 1;
}

//���á���ѯ���
int do_vip(string arg)
{
        string msg;
        if (arg)
                msg = HEIDIAN_D->do_vip(this_object(),this_player(),arg);
        else
                msg = HEIDIAN_D->list_vip(this_object(),this_player());
        write(msg);
        return 1;
}

//���á���ѯ���
int do_unwelcome(string arg)
{
        string msg;
        if (arg)
                msg = HEIDIAN_D->do_unwelcome(this_object(),this_player(),arg);
        else
                msg = HEIDIAN_D->list_unwelcome(this_object(),this_player());
        write(msg);
        return 1;
}

string query_save_file()
{
        string id;

        id = query("shop_id");
        if( !stringp(id) ) return 0;
        return sprintf(DATA_DIR "/shop/%s", id);
}

int save()
{
        string file;

        if( stringp(file = this_object()->query_save_file()) ) {
                assure_file(file + __SAVE_EXTENSION__);
                return save_object(file);
        }
        return 0;
}

int restore()
{
        string file;
        if( stringp(file = this_object()->query_save_file()) && file_size(file + __SAVE_EXTENSION__) > 0 )
                return restore_object(file);
        return 0;
}