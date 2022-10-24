#include <core.p4>
#define V1MODEL_VERSION 20200408
#include <v1model.p4>

header data_t {
    bit<32> x;
}

struct metadata {
}

struct headers {
    @name(".data")
    data_t data;
}

parser ParserImpl(packet_in packet, out headers hdr, inout metadata meta, inout standard_metadata_t standard_metadata) {
    @name(".start") state start {
        packet.extract<data_t>(hdr.data);
        transition accept;
    }
}

control egress(inout headers hdr, inout metadata meta, inout standard_metadata_t standard_metadata) {
    apply {
    }
}

control ingress(inout headers hdr, inout metadata meta, inout standard_metadata_t standard_metadata) {
    @noWarn("unused") @name(".NoAction") action NoAction_1() {
    }
    @name(".my_drop") action my_drop() {
        mark_to_drop(standard_metadata);
    }
    @name(".set_egress_port") action set_egress_port(@name("egress_port") bit<9> egress_port_1) {
        standard_metadata.egress_spec = egress_port_1;
    }
    @name(".repeater") table repeater_0 {
        actions = {
            my_drop();
            set_egress_port();
            @defaultonly NoAction_1();
        }
        key = {
            standard_metadata.ingress_port: exact @name("standard_metadata.ingress_port");
        }
        default_action = NoAction_1();
    }
    apply {
        repeater_0.apply();
    }
}

control DeparserImpl(packet_out packet, in headers hdr) {
    apply {
        packet.emit<data_t>(hdr.data);
    }
}

control verifyChecksum(inout headers hdr, inout metadata meta) {
    apply {
    }
}

control computeChecksum(inout headers hdr, inout metadata meta) {
    apply {
    }
}

V1Switch<headers, metadata>(ParserImpl(), verifyChecksum(), ingress(), egress(), computeChecksum(), DeparserImpl()) main;
