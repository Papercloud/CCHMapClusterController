//
//  CCHMapClusterController.h
//  CCHMapClusterController
//
//  Copyright (C) 2013 Claus Höfele
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#import <Foundation/Foundation.h>
#import <MapKit/MapKit.h>

@protocol CCHMapClusterControllerDelegate;
@protocol CCHMapClusterer;
@protocol CCHMapAnimator;

/**
 Controller to cluster annotations. Automatically updates clustering when user zooms or pans the map.
 */
@interface CCHMapClusterController : NSObject

/** Clustered annotations. */
@property (nonatomic, copy, readonly) NSSet *annotations;
/** Map view to display clustered annotations. */
@property (nonatomic, strong, readonly) MKMapView *mapView;

/** Multiplier to extend visible area that's included for clustering (default: 0.5). */
@property (nonatomic, assign) double marginFactor;
/** Cell size in [points] (default: 60). */
@property (nonatomic, assign) double cellSize;
/** Displays the grid used for clustering. */
@property (nonatomic, assign, getter = isDebuggingEnabled) BOOL debuggingEnabled;

/** Delegate to configure cluster annotations. */
@property (nonatomic, weak) id<CCHMapClusterControllerDelegate> delegate;

/** Delegate to define strategy for positioning cluster annotations (default: `CCHCenterOfMassMapClusterer`). */
@property (nonatomic, weak) id<CCHMapClusterer> clusterer;
/** Reuse existing cluster annotations for a cell (default: `YES`). */
@property (nonatomic, assign) BOOL reuseExistingClusterAnnotations;

/** Delegate to define strategy for animating cluster annotations in and out (default: `CCHFadeInOutMapAnimator`). */
@property (nonatomic, weak) id<CCHMapAnimator> animator;

/**
 Set center coordinate without re-drawing clusters and while maintaining the zoom level.
 */
- (void)setCenterCoordinateWithoutRecluster:(CLLocationCoordinate2D)location animated:(BOOL)animated;

/**
 Select an annotation and keep it selected and visible as a cluster of one regardless of clustering or zoom level.
 Intended to be called from within mapView:didSelectAnnotationView:
 @param annotation An annotation as added with addAnnotations:withCompletionHandler:. Not to be a CCHMapClusterAnnotation.
 */
- (void)selectAnnotation:(id<MKAnnotation>)annotation;

/**
 Same as selectAnnotation, but immediately updates clustering so the selected pin will show immediately.
 */
- (void)selectAndUpdateAnnotation:(id<MKAnnotation>)annotation;

/**
 Deselect an annotation, so it can be included within other clusters.
 Intended to be called from mapView:didDeselectAnnotationView:
 @param annotation An annotation as added with addAnnotations:withCompletionHandler:. Not to be a CCHMapClusterAnnotation.
 */
- (void)deselectAnnotation:(id<MKAnnotation>)annotation;

/**
 Deselect all annotations, usually to prepare for selecting another.
 */
- (void)deselectAllAnnotations;

/**
 Returns TRUE if any of annotations are currently selected.
 */
- (BOOL)hasSelectedAnnotations:(NSSet *)annotations;

/**
 Initializes the cluster controller.
 @param mapView `MKMapView` to use to display clusters.
 */
- (id)initWithMapView:(MKMapView *)mapView;

/** 
 Adds annotations and immediately updates clustering.
 @param annotations Annotations to add.
 @param completionHandler Called when the clustering finished updating.
 */
- (void)addAnnotations:(NSArray *)annotations withCompletionHandler:(void (^)())completionHandler;

/**
 Removes annotations and immediately updates clustering.
 @param annotations Annotations to add.
 @param completionHandler Called when the clustering finished updating.
 */
- (void)removeAnnotations:(NSArray *)annotations withCompletionHandler:(void (^)())completionHandler;

/**
 Removes all annotations and immediately updates clustering.
 @param completionHandler Called when the clustering finished updating.
 */
- (void)removeAllAnnotationsWithCompletionHandler:(void (^)())completionHandler;

/** 
 Zooms to the position of the cluster that contains the given annotation and selects the cluster's annotation view.
 @param annotation The annotation to look for. Uses `isEqual:` to check for a matching annotation previously added with `addAnnotations:withCompletionHandler:`.
 @param latitudinalMeters North-to-south distance used for zooming.
 @param longitudinalMeters East-to-west distance used for zooming.
 */
- (void)selectAnnotation:(id<MKAnnotation>)annotation andZoomToRegionWithLatitudinalMeters:(CLLocationDistance)latitudinalMeters longitudinalMeters:(CLLocationDistance)longitudinalMeters;

@end
