// DOOM BSP
// @see https://github.com/id-Software/DOOM
// @see https://github.com/id-Software/DOOM/blob/master/linuxdoom-1.10/r_bsp.c#L552
void R_RenderBSPNode(int bspnum) {
    if (bspnum & NF_SUBSECTOR) R_Subsector(bspnum & ~NF_SUBSECTOR); return;

    node_t *bsp = &nodes[bspnum];
    int side = R_RenderBSPNode(viewx, viewy, bsp);

    R_RenderBSPNode(bsp->children[side]);

    if (R_CheckBBox(bsp->bbox[side ^ 1]))
        R_RenderBSPNode(bsp->children[side ^ 1]);
}