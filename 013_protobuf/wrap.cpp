#include "wrap.h"

#include "protomsg.pb.h"

void c_wrap_protobuf_verify_version(){
    GOOGLE_PROTOBUF_VERIFY_VERSION;
}

void c_wrap_protobuf_shutdown_library(){
    google::protobuf::ShutdownProtobufLibrary();
}

void* c_wrap_protobuf_image_unmarshal(void *data, const size_t size){
    protomsg::Image *img = new protomsg::Image();
    if (!img->ParseFromArray(data, size)){
        delete img;
        return NULL;
    }

    return img;
}

void c_wrap_protobuf_image_release(void *img){
    if (img){
        protomsg::Image *t = (protomsg::Image*)img;
        delete t;
    }
}

unsigned char *c_wrap_protobuf_image_get(void *img, int *w, int *h, int *c){
    if (!img) return NULL;
    
    protomsg::Image *t = (protomsg::Image*)img;
    *w = t->width();
    *h = t->height();
    *c = 3;

    return (unsigned char*)t->data().c_str();
}

int c_wrap_protobuf_image_get_all_info(void *img, unsigned char **img_data, int *img_w, int *img_h, int *img_c,
    char **cid, char **cname, char **stamp, int64_t *img_id){

    if (!img) return -1;
    
    protomsg::Image *t = (protomsg::Image*)img;

    *img_data = (unsigned char*)t->data().c_str();
    *img_w = t->width();
    *img_h = t->height();
    *img_c = 3;

    *cid = (char*)t->cid().c_str();
    *cname = (char*)t->cname().c_str();
    *stamp = (char*)t->timestamp().c_str();

    *img_id = t->id();
    
    return 0;
}

void* c_wrap_protobuf_rulemsg_unmarshal(void *data, const size_t size){
    protomsg::RuleMessage *rulemsg = new protomsg::RuleMessage();

    if (size > 0){
        rulemsg->ParseFromArray(data, size);
    }

    return rulemsg;
}

void* c_wrap_protobuf_rulemsg_add_sdkmsg(void *rmsg, const char* dtype, const char *sdktype, 
    const char *sdkid, const char *sdkname, const char *stamp){

    if (!rmsg) return NULL;
    protomsg::RuleMessage *rulemsg = (protomsg::RuleMessage*)rmsg;
    rulemsg->set_datatype(dtype);

    auto ht = rulemsg->handletrack();
    if (!ht.empty()){
        rulemsg->set_handletrack(ht + "___" + sdktype);
    }

    protomsg::SDKMessage *sdkmsg = rulemsg->add_message();
    sdkmsg->set_sdkid(sdkid);
    sdkmsg->set_sdktype(sdktype);
    sdkmsg->set_sdkname(sdkname);
    sdkmsg->set_timestamp(stamp);

    return sdkmsg;
}

int c_wrap_protobuf_sdkmsg_add_target(void *smsg, const uint64_t *id, const int confidence,
    const int l, const int t, const int r, const int b, 
    const char *feat, const int feat_size, const char *attr, const int attr_size){

    if (!smsg) return -1;

    protomsg::SDKMessage *sdkmsg = (protomsg::SDKMessage *)smsg;

    protomsg::Target *tp = sdkmsg->add_target();
    tp->set_id(*id);
    tp->set_confidence(confidence);
    protomsg::Rect *rc = tp->mutable_rect();
    rc->set_left(l);
    rc->set_top(t);
    rc->set_right(r);
    rc->set_bottom(b);
    tp->set_type(sdkmsg->sdktype());
    if (!feat){
        tp->set_feature("");
    }else{
        tp->set_feature(feat, feat_size);
    }
    if (!attr){
        tp->set_attribute("");
    }else{
        tp->set_attribute(attr, attr_size);
    }

    return 0;
}

int c_wrap_protobuf_rulemsg_release_and_update(void *rmsg, void *data){

    if (!rmsg)return -1;

    protomsg::RuleMessage *rulemsg = (protomsg::RuleMessage*)rmsg;
    size_t size = rulemsg->ByteSizeLong();
    memcpy(data, &size, sizeof(size_t));
    rulemsg->SerializeToArray((char*)data+sizeof(size_t), size);

    delete rulemsg;

    return 0;
}

int c_wrap_protobuf_last_sdkmsg_targets_count(void *rmsg){
    protomsg::RuleMessage *rulemsg = (protomsg::RuleMessage*)rmsg;
    if (rulemsg->message_size() == 0) return 0;
    auto &sdkmsg = rulemsg->message(rulemsg->message_size() - 1);
    return sdkmsg.target_size();
}

int c_wrap_protobuf_last_sdkmsg_targets_get(void *rmsg, const int index,
    int *l, int *t, int *r, int *b, int *confidence){

    protomsg::RuleMessage *rulemsg = (protomsg::RuleMessage*)rmsg;
    if (rulemsg->message_size() == 0) return -1;
    auto &sdkmsg = rulemsg->message(rulemsg->message_size() - 1);
    if (sdkmsg.target_size() <= index) return -1;

    auto &target = sdkmsg.target(index);
    *l = target.rect().left();
    *t = target.rect().top();
    *r = target.rect().right();
    *b = target.rect().bottom();
    *confidence = target.confidence();

    return 0;
}
