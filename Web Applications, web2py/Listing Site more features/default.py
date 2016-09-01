# -*- coding: utf-8 -*-

def create():
    form = SQLFORM(db.listing).process(next=URL('index'))
    return dict(form=form)

def index():
    posts = db().select(db.listing.ALL, orderby=db.listing.title)
    return dict(posts=posts)

def show():
    num = request.args[0]
    post = db.listing(request.args(0,cast=int)) or redirect(URL('index'))
    imgs = db(db.images.post_ID==post.id).select()
    postID=post.id
    return locals()

def available():
    posts = db().select(db.listing.ALL, orderby=db.listing.title)
    return locals()

@auth.requires_login()
def upload_new_image():
    postID = request.args[0]
    db.images.post_ID.default = postID 
    form=SQLFORM(db.images).process(next=URL(('show'), args=postID))
    return dict(form=form)

def viewimage():
    image = request.args[0]
    postID = request.args[1]
    return locals()
       
def rating():
    vars = request.post_vars
    if vars:
        poster = vars.id
        value = vars.updown
        if db((db.voting.ratee==poster)&(db.voting.rater==auth.user.id)).select():
            ratee = db(db.auth_user.id==poster).select().first()
            rater = db((db.voting.ratee==poster)&(db.voting.rater==auth.user.id)).select().first()
            if rater.updown=="up":
                if value=="up":
                    ratee.update_record(rating=(ratee.rating-1))
                    ratee.update_record(numberofvotes=(ratee.numberofvotes-1))
                    ratee.update_record(positivevotes=(ratee.positivevotes-1))
                    db(db.voting.id == rater.id).delete()
                    response.flash="You canceled your vote."
                elif value=="down":
                    rater.update_record(updown='down')
                    ratee.update_record(rating=(ratee.rating-2))
                    ratee.update_record(positivevotes=(ratee.positivevotes-1))
                    ratee.update_record(negativevotes=(ratee.negativevotes+1))
                    response.flash="You changed your vote."
            elif rater.updown=="down":
                if value=="up":
                    rater.update_record(updown='up')
                    ratee.update_record(rating=(ratee.rating+2))
                    ratee.update_record(positivevotes=(ratee.positivevotes+1))
                    ratee.update_record(negativevotes=(ratee.negativevotes-1))
                    response.flash="You changed your vote."

                elif value=="down":
                    ratee.update_record(rating=(ratee.rating+1))
                    db(db.voting.id == rater.id).delete()
                    ratee.update_record(numberofvotes=(ratee.numberofvotes-1))
                    ratee.update_record(negativevotes=(ratee.negativevotes-1))
                    response.flash="You canceled your vote."
            return str(ratee.rating)
        else:
            ratee = db(db.auth_user.id==poster).select()[0]
            if ratee.id == auth.user.id:
                response.flash="This is your post."
            else:
                if value == "up":
                    ratee.update_record(rating=ratee.rating + 1)
                    db.voting.insert(ratee=poster, updown="up", rater=auth.user.id)
                    ratee.update_record(numberofvotes=(ratee.numberofvotes+1))
                    ratee.update_record(positivevotes=(ratee.positivevotes+1))
                elif value == "down":
                    ratee.update_record(rating=ratee.rating - 1)
                    db.voting.insert(ratee=poster, updown="down", rater=auth.user.id)
                    ratee.update_record(numberofvotes=(ratee.numberofvotes+1))
                    ratee.update_record(negativevotes=(ratee.negativevotes+1))
            return str(ratee.rating)

def manage():
    grid = SQLFORM.grid(db.listing)
    return locals()

def download():
    return response.download(request, db)

def login():
    form2 = SQLFORM(db.auth_user).process()
    return locals()

def other():
    message = 'Welcome %s' % request.vars.your_name
    return locals()

def user():
    """
    exposes:
    http://..../[app]/default/user/login
    http://..../[app]/default/user/logout
    http://..../[app]/default/user/register
    http://..../[app]/default/user/profile
    http://..../[app]/default/user/retrieve_password
    http://..../[app]/default/user/change_password
    http://..../[app]/default/user/bulk_register
    use @auth.requires_login()
        @auth.requires_membership('group name')
        @auth.requires_permission('read','table name',record_id)
    to decorate functions that need access control
    also notice there is http://..../[app]/appadmin/manage/auth to allow administrator to manage users
    """
    return dict(form=auth())


@cache.action()
def download():
    """
    allows downloading of uploaded files
    http://..../[app]/default/download/[filename]
    """
    return response.download(request, db)


def call():
    """
    exposes services. for example:
    http://..../[app]/default/call/jsonrpc
    decorate with @services.jsonrpc the functions to expose
    supports xml, json, xmlrpc, jsonrpc, amfrpc, rss, csv
    """
    return service()
